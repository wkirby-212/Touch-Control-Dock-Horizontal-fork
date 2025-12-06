# Touch Control Dock — v6

A touch-first control surface built as a small proof-of-concept:
- A minimal **OBS frontend plugin** (adds a simple help dock).
- A **touch-friendly HTML UI** intended for a **Browser Dock**.
- Control is performed via the built-in **websocket v5** server.

This UI is designed for fast, reliable operation on PC Attached touch Panels:
- Big buttons and sliders.
- Sticky section navigation.
- A favorites panel for your most-used scenes and audio.
- Collapsible audio groups with an optional group-only filter.

---

## What’s in this package

```
touch-control-dock/
  README.md
  src/
    plugin-main.cpp
  data/
    touch-ui/
      index.html
```

### `src/plugin-main.cpp`
A minimal frontend module that adds a small “Touch Control Help” dock.
It exists mainly to confirm the plugin is loaded and to provide quick usage notes.

### `data/touch-ui/index.html`
The main touch UI. This is what you load in an OBS Browser Dock.

---

## Requirements

- OBS Studio with **obs-websocket v5** support enabled.
  (OBS bundles this in recent versions.)
- A local connection (default):
  - Host: `127.0.0.1`
  - Port: `4455`
- A password if you enabled authentication in WebSocket settings.

---

## Install / Build

This is a feature pack rather than a full build system.

Recommended approach:

Quick Start Guide
Download the contents of the repository, and drop the extracted files into 
  - `C:\Program Files\obs-studio\obs-plugins\64bit\
  - make a new directory `touch-control-dock` 
  - Extract files to this directory. 
  - go to `*\touch-control-dock\data\touch-ui\` and open index.html 
  - Input your Host port and Password then hit connect.

Alternative:
1. Start from the official OBS plugin template.
2. Copy:
   - `src/plugin-main.cpp`
   - `data/touch-ui/`
3. Ensure your build installs the `data/` folder with the plugin.

If you don’t care about the tiny native help dock, you can skip the C++ part:
the HTML UI can be used standalone with a Browser Dock.

---

## Setup (runtime)

1. **Enable WebSocket**
   - `Tools -> WebSocket Server Settings`
   - Enable server and set a password if desired.

2. **Add a Browser Dock**
   - `View -> Docks -> Custom Browser Docks`
   - Name: `Touch Control`

3. **Point the dock to the UI**
   - Option A (fastest):
     - Use a `file:///` path to `data/touch-ui/index.html`
   - Option B (more reliable):
     - Serve the folder on localhost and use an `http://127.0.0.1:PORT/index.html` URL.

4. Enter **Host / Port / Password** in the UI and tap **Connect**.

---

## Features

### Quick Jump bar
A sticky, touch-friendly nav strip for:
- Top
- Favorites
- Studio
- Scenes
- Transitions
- Audio

### Favorites
Stored in your browser’s localStorage:
- **Favorite Scenes**
  - One-tap program switching.
- **Favorite Audio**
  - Compact mini-cards with volume + mute controls.

To use:
- Tap ☆ on any scene or audio card to add a favorite.
- Favorites appear in the top panel.

### Studio Mode
- Enable/disable Studio Mode.
- Preview scene selection.
- Program scene selection.
- “Take” button.

### Transitions
- Choose current transition.
- Set duration (ms).
- Quick transition buttons.

### Audio / Inputs
- Lists **audio-capable inputs** by probing:
  - `GetInputVolume`
  - `GetInputMute`
- Per-input meters (best-effort) from:
  - `InputVolumeMeters` events.
- Volume slider + mute controls.
- Handy preset buttons (0% / 100% / 150%).

### Source Group support (collapsible)
The UI attempts to read:
- `GetGroupList`
- `GetGroupSceneItemList`

Then maps audio inputs into those Source Groups.
Anything else appears in **Ungrouped**.

Groups are rendered as an **accordion**:
- Opening one group collapses the others.

### Audio Group Filter
A top-of-mixer control that lets you:
- Toggle filtering ON/OFF.
- Pick which Source Groups should show.
- Quickly “Select All” or clear.

When filtering is ON:
- The UI shows only the groups you selected
  (designed for clean cast-only Touch Panel views).

### Scene Collections & Profiles
Dropdowns to switch:
- Current Scene Collection
- Current Profile

---

## Known limitations / caveats

- OBS request names can vary slightly by version.
  The UI includes some fallback logic, but older builds may behave differently.
- Some inputs may appear “audio-capable” even if they’re not meaningful
  mixer channels in your workflow.
  The group filter + favorites are the intended way to keep your Touch Panel view clean.
- Meter event formats can differ; the UI uses a conservative best-effort parse.

---

## Customisation

Open:
`data/touch-ui/index.html`

### Theme
I like the black and gold look personally, but adjust these variables to your liking:

```css
--bg: #0b0b0e;
--surface: #111217;
--surface-2: #161821;
--gold: #d7b25e;
--gold-2: #b8932f;
```

### Rename-based filtering (optional)
If you want a hard filter by name, add a simple check in `getAudioCapableInputs()`.

---

## Suggested “best practice” layout for your use case

For a multi-person show:

1. Create a Source Group called:
   - `Cast`
2. Put your voice inputs inside it:
   - Host, Person 1, Person 2, etc.
3. Add a second group:
   - `Music`
4. Enable the UI group filter and select only:
   - Cast
   - Music

Then pin key items to favourites.

---

## License

This proof-of-concept code is intended as a starting point.
Use and adapt freely within your project.
