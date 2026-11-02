#!/usr/bin/env python3
"""Static integrity checks for the CINEMAX web application."""
from html.parser import HTMLParser
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
HTML = ROOT / "index.html"
JS = ROOT / "assets" / "app.js"

class PageParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.ids = []
        self.refs = []
    def handle_starttag(self, tag, attrs):
        attrs = dict(attrs)
        if attrs.get("id"):
            self.ids.append(attrs["id"])
        for attr in ("src", "href"):
            value = attrs.get(attr, "")
            if value and not value.startswith(("http://", "https://", "#", "data:", "mailto:", "javascript:")):
                self.refs.append(value)

def fail(message):
    print("ERROR:", message, file=sys.stderr)
    raise SystemExit(1)

if not HTML.is_file() or not JS.is_file():
    fail("index.html or assets/app.js is missing")

page = HTML.read_text(encoding="utf-8")
code = JS.read_text(encoding="utf-8")
parser = PageParser()
parser.feed(page)

duplicates = sorted({item for item in parser.ids if parser.ids.count(item) > 1})
if duplicates:
    fail("Duplicate HTML IDs: " + ", ".join(duplicates))

# The app uses the $() helper with literal CSS selectors. Verify direct ID lookups.
selectors = set(re.findall(r"\$\(['\"]#([A-Za-z0-9_-]+)['\"]\)", code))
missing = sorted(selectors - set(parser.ids))
if missing:
    fail("JavaScript references missing HTML IDs: " + ", ".join(missing))

missing_refs = []
for value in parser.refs:
    target = (ROOT / value).resolve()
    if (ROOT.resolve() not in target.parents and target != ROOT.resolve()) or not target.is_file():
        missing_refs.append(value)
if missing_refs:
    fail("Missing or unsafe local references: " + ", ".join(sorted(set(missing_refs))))

print(f"Integrity OK: {len(parser.ids)} IDs, {len(selectors)} literal JS ID selectors, {len(parser.refs)} local references.")
