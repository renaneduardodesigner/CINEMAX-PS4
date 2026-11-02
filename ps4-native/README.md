# CINEMAX PS4 Native — FPKG build

This directory contains the first native OpenOrbis homebrew shell for CINEMAX.

## Build

The GitHub Actions workflow \`.github/workflows/build-ps4-fpkg.yml\` uses OpenOrbis Toolchain v0.5.1 in a cloud runner. It creates an FPKG artifact named \`CINEMAX-PS4-FPKG\`.

## Controls

- D-pad left/right: change the selected tile.
- Cross (X): open the CINEMAX web catalog in the PS4 browser.
- Circle (O): return the status label to the home screen.

## Important scope

This native package is a PS4 launcher shell. The catalog, search, metadata and web content remain in the existing web application, opened in the PS4 browser. It does not embed a WebKit engine, does not contain a licensed streaming service, and does not decrypt, bypass DRM, or provide unauthorized video sources. Browser launch depends on the system service being available in the target firmware/runtime.

Target requested by the owner: PS4 GoldHEN, firmware 13.52. No console test is performed by this workflow.
