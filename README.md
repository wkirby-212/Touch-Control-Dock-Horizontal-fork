# Touch Control Dock — v8

A touch-first control surface intended for use with OBS via **obs-websocket v5**.

This package includes:
- A minimal native frontend module (`src/plugin-main.cpp`) that adds a small help dock.
- A touch-friendly HTML UI (`data/touch-ui/index.html`) for an OBS **Browser Dock**.

The HTML UI is the primary deliverable; the C++ dock is optional.

---

## What’s new in v8

- **HYTE Y70 Touch layout support**
  - Auto-detects ultra-wide, short displays.
  - Manual override via the in-UI **Layout** selector.
  - Hard override via URL:
    - `?layout=y70`

---

## Features

- Scene switching
- Studio Mode controls (Preview / Program / Take)
- Transition selection + duration
- Scene Collections + Profiles switching
- Audio mixer controls
- **Per-input meters** (best-effort via WebSocket events)
- **Source Group accordion**
- **Audio Group Filter**
- **Favorites** (scenes + audio)
- **Live Controls**
  - Start/Stop Streaming
  - Start/Stop Recording
  - Status badges

---

## Setup

1. Enable WebSocket:
   - `Tools -> WebSocket Server Settings`
2. Add a Browser Dock:
   - `View -> Docks -> Custom Browser Docks`
3. Point it at:
   - `file:///.../data/touch-ui/index.html`
   - or serve the folder via localhost and use an `http://` URL.
4. Enter Host/Port/Password and connect.

---

## HYTE Y70 Touch quick tip

For your ultra-wide internal panel:
- Use a dock URL like:
  - `file:///.../index.html?layout=y70`

This forces the compact, wide-strip layout.

---

## Notes

- Favorites and filtering preferences are stored in `localStorage`.
- Audio grouping uses OBS **Source Groups** when available.