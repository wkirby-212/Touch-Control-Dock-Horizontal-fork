# OBS Touch Control Dock — v6 (Write-up)

This project started as a practical answer to a common OBS workflow problem:
**touch control without extra hardware**.

You wanted a control surface that:
- runs on the same machine as OBS,
- is touch-friendly,
- gives fast access to scenes and audio,
- and avoids the friction of scrolling or digging through standard docks.

Rather than reinventing the entire OBS UI in C++/Qt,
the approach here deliberately splits responsibilities:

1. **Native plugin (minimal)**
   - Adds a tiny “help/confirm loaded” dock.
   - Keeps the build surface small and stable.

2. **Touch UI (HTML)**
   - Gives us rapid iteration on layout and usability.
   - Works cross-platform (Windows/macOS/Linux) as long as OBS can run a Browser Dock.
   - Connects through obs-websocket v5, which is already part of modern OBS setups.

This makes the system flexible:
if OBS changes dock APIs or you want to remove the native part,
you can still keep the same UI.

---

## Why the UI was reorganized

### The “long scroll” problem
Once we added:
- Studio Mode,
- transitions,
- scene collections/profiles,
- audio grouping,
- meters,

the single-page layout became feature-rich but less efficient on a tablet.

The solution was not to split into multiple pages (which adds navigation cost),
but to reduce *hand travel* and *scroll distance* with two tactics:

1. **Sticky Quick Jump**
   - Large tap targets pinned near the top of the page.
   - Smooth jumps to major sections.

2. **Favorites**
   - A top-level “fast lane” for what you *actually use during a live session*.
   - This removes the need to scroll to access core pieces
     like cast mics or your three most used scenes.

---

## Why “Source Groups” were used

OBS already provides an organizational concept that maps well to
a touch layout: **Source Groups**.

By discovering groups via WebSocket and mapping inputs to them,
we can present a UI that mirrors how you’ve mentally structured your show.

That’s why v6 also added:

- **Accordion behavior**
  - Reduces visual overload.
  - Helps you focus on one audio “cluster” at a time.

- **Group-only filter**
  - Lets you turn the tablet into a curated “production deck”
    instead of a raw list of everything in OBS.

---

## What this UI does well now

### For your D&D show format
This is a strong fit for:
- quick scene swaps between
  - Fireside Chat,
  - Game Board,
  - Intro Art
- rapid cast mic balancing
- instant music/cue control

The biggest win is friction reduction during a live recording:
the UI favors “big obvious buttons that do one thing well” over dense controls.

---

## Technical notes (high-level)

- Audio-capable inputs are discovered by **probing**
  `GetInputVolume` and `GetInputMute`
  rather than guessing by input kind.
  This is safer across different OBS plugin ecosystems.

- Meters rely on the `InputVolumeMeters` event stream.
  The parsing is conservative because the event payload formats
  can vary between builds.

- Favorites and filter settings use localStorage.
  This keeps the UI stateless on the OBS side and easy to back up.

---

## Ideas if you want to push this further

1. **Preset layouts**
   - “Session Mode” vs “Fireside Mode”
   - auto-toggle group filters and favorites visibility.

2. **Multi-device sync**
   - Store favorites in a small JSON file served from localhost
     so multiple tablets share the same config.

3. **Role-based views**
   - A simplified “producer” view
   - A “DM-only” audio panel

4. **Safer meter mapping**
   - Add a small UI toggle to enable/disable meters
     if you ever notice performance impact.

---

## Bottom line

v6 is a clean, touch-first control surface that solves the real-world pain:
**fast access with minimal scrolling**.

It’s a practical, modular design:
- simple native footprint,
- powerful, customizable touch UI,
- and enough structure (groups + favorites)
  to scale cleanly as your show grows.