TITLE       := CINEMAX PS4
VERSION     := 1.00
TITLE_ID    := CMAX00001
CONTENT_ID  := IV0000-CMAX00001_00-CINEMAXPS4APP000

LIBS        := -lc -lkernel -lc++ -lSceVideoOut -lScePad -lSceUserService
TOOLCHAIN   := $(OO_PS4_TOOLCHAIN)
PROJDIR     := src
INTDIR      := $(PROJDIR)/x64/Debug
CXXFILES    := $(wildcard $(PROJDIR)/*.cpp)
OBJS        := $(patsubst $(PROJDIR)/%.cpp,$(INTDIR)/%.o,$(CXXFILES))

CXXFLAGS    := --target=x86_64-pc-freebsd12-elf -fPIC -funwind-tables -c -isysroot $(TOOLCHAIN) -isystem $(TOOLCHAIN)/include -isystem $(TOOLCHAIN)/include/c++/v1
LDFLAGS     := -m elf_x86_64 -pie --script $(TOOLCHAIN)/link.x --eh-frame-hdr -L$(TOOLCHAIN)/lib $(LIBS) $(TOOLCHAIN)/lib/crt1.o
CDIR        := linux

.PHONY: all clean check-toolchain
.DEFAULT_GOAL := all

all: check-toolchain $(CONTENT_ID).pkg

check-toolchain:
	@test -n "$(TOOLCHAIN)" || (echo "OO_PS4_TOOLCHAIN is not set" >&2; exit 1)
	@test -x "$(TOOLCHAIN)/bin/linux/PkgTool.Core" || (echo "PkgTool.Core missing from OpenOrbis toolchain" >&2; exit 1)
	@test -x "$(TOOLCHAIN)/bin/linux/create-eboot" || (echo "create-eboot missing from OpenOrbis toolchain" >&2; exit 1)
	@command -v clang++ >/dev/null || (echo "clang++ is not available" >&2; exit 1)
	@command -v ld.lld >/dev/null || (echo "ld.lld is not available" >&2; exit 1)

sce_sys/icon0.png:
	python3 scripts/create_icon.py

sce_sys/param.sfo: Makefile
	mkdir -p sce_sys
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_new $@
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ APP_TYPE --type Integer --maxsize 4 --value 1
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ APP_VER --type Utf8 --maxsize 8 --value '$(VERSION)'
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ ATTRIBUTE --type Integer --maxsize 4 --value 0
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ CATEGORY --type Utf8 --maxsize 4 --value gd
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ CONTENT_ID --type Utf8 --maxsize 48 --value '$(CONTENT_ID)'
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ DOWNLOAD_DATA_SIZE --type Integer --maxsize 4 --value 0
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ SYSTEM_VER --type Integer --maxsize 4 --value 0
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ TITLE --type Utf8 --maxsize 128 --value '$(TITLE)'
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ TITLE_ID --type Utf8 --maxsize 12 --value '$(TITLE_ID)'
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core sfo_setentry $@ VERSION --type Utf8 --maxsize 8 --value '$(VERSION)'

$(INTDIR):
	mkdir -p $(INTDIR)

$(INTDIR)/%.o: $(PROJDIR)/%.cpp | $(INTDIR)
	clang++ $(CXXFLAGS) -o $@ $<

# The GP4 manifest expects the executable at the package root as eboot.bin.
# Do not leave it only in the intermediate build directory.
eboot.bin: $(OBJS)
	ld.lld $(OBJS) -o $(INTDIR)/cinemax.elf $(LDFLAGS)
	$(TOOLCHAIN)/bin/$(CDIR)/create-eboot -in=$(INTDIR)/cinemax.elf -out=$@ --paid 0x3800000000000011
	test -s $@

$(CONTENT_ID).pkg: pkg.gp4 eboot.bin sce_sys/param.sfo sce_sys/icon0.png
	test -s eboot.bin
	test -s sce_sys/param.sfo
	test -s sce_sys/icon0.png
	$(TOOLCHAIN)/bin/$(CDIR)/PkgTool.Core pkg_build $< .

clean:
	rm -rf $(INTDIR) eboot.bin $(CONTENT_ID).pkg sce_sys/param.sfo
	# Keep icon0.png: CI generates it on the host before the toolchain container runs.
