# 🌵 Cactus Game – Game Jam Project

**Developer:** MRJettie  
**Engine:** Unreal Engine 5.4 (C++)  
**Status:** Work in Progress  
**Planned Release:** Free on Steam after Game Jam  
**Last Updated:** October 2025  

---

## 🎮 Overview
**Cactus Game** is a small Unreal Engine 5.4 project built primarily in **C++** for a Game Jam and personal growth as a developer.  
The player must keep their **Baby Cactus** alive by collecting enough resources from dangerous desert zones, while fighting rival cacti and upgrading their abilities across runs.

---

## 🌵 Project Vision
**Cactus Game** is a resource-driven survival adventure where the player must keep their Baby Cactus alive by venturing out to gather water from hostile desert areas.

The cactus isn’t always under attack, but its survival depends entirely on the player’s ability to bring back enough resources before it dries out. Each run challenges players to balance risk versus reward, deciding which areas to explore and how much danger to face for better loot.

### 🌍 Gameplay Overview
- **Protect and Sustain:** The Baby Cactus requires a specific amount of **water and resources** each run. Failing to gather enough before time runs out results in the cactus **withering and dying**.
- **Expedition Gameplay:** Leave your safe zone to explore and collect resources in enemy-infested areas. Return to the cactus to deliver what you’ve gathered.
- **Dynamic Levels & Modifiers:** Choose between multiple areas, each with unique modifiers.  
  - *Example:* One level may be easier but yield less water, while another offers double drops with tougher enemies.
- **Scaling Difficulty:** Every few levels introduce **mini-boss enemies** that must be prioritized to avoid being overwhelmed.
- **Enemy Variety:** Encounter melee bruisers, ranged attackers, and explosive “bomber” cacti that keep you on your toes.
- **Progression & Builds:**  
  - Earn **coins** and **XP** from combat and completed runs.  
  - Spend coins at **vendors** between levels to purchase upgrades.  
  - Use skill points from leveling to define your playstyle — create a **tank build** (high defense and HP) or a **glass cannon** (high damage, low defense).  
- **Future Plans:** Introduce multiple playable characters with distinct stats and playstyles.  
  - *Example:* **Brawler** – high damage resistance and HP, but slower movement speed.

### 🎯 Design Goal
Keep the systems **simple yet satisfying**, focusing on **tight combat**, **rewarding resource loops**, and **meaningful progression**.  
While built primarily for learning and experience (~90% C++ / 10% Blueprints), the project is designed with long-term scalability and potential Steam release in mind.

---

## 🧩 Core Systems

### 🪖 Weapons
- **BaseWeapon class** with two child classes for different weapon types.
- Supports **pickup**, **equip**, and **fire** logic.
- **Weapon switching** system under development.
- UI elements dynamically update based on the equipped weapon.

### 🧺 Inventory
- Modular `UInventoryComponent` for tracking player-held resources and XP coins.
- Coins and XP will later integrate with vendors and level-based scaling.
- Designed to be easily extendable for future items and currencies.

### 💚 Health Component
- Custom `UHealthComponent` designed for **reusability** across both **player** and **enemy** classes.
- Provides shared health and damage logic for all actors.
- Will later include **damage resistance**, **healing**, and **death handling**.

### 🌱 Baby Cactus Progression
- Config-based progression system that tracks resources delivered.
- Baby Cactus grows and levels up based on collected water/resources.
- Simplified resource model: instead of multiple item types (Small Water, Large Water, etc),  
  each **BasePickup child class** now acts as a **multiplier** (e.g., +1, +5 Water).

### 💎 Pickups
- Simplified into a single `ABasePickup` class hierarchy.  
- Child pickups modify reward values via multipliers for flexible balancing.  
- Cleaner than managing multiple hardcoded item types.

---

## 🧠 Current Goals / TODO
- ⚙️ Fix weapon switching logic and ensure UI synchronization  
- 🧍‍♂️ Implement enemy spawning and basic damage interaction (no AI behavior yet)  
- 💰 Add enemy loot drops for **coins**, **XP**, or **resource multipliers**  
- 💪 Extend HealthComponent with resistance and healing functionality  
- 🛠️ Add vendor/XP systems for upgrades and level-based damage scaling  
- 🎨 Continue polish and optimization for release build  

---

## 🐞 Known Issues
- Weapon switching and UI desync after swaps  
- Secondary weapon either completely disappears or overlaps primary weapon  
- Primary weapon displays correct information while secondary weapon only provides weapon name in the ui

---

## 🧰 Technical Details
- Developed in **Unreal Engine 5.4**
- Written in approximately **90% C++ and 10% Blueprints**
  - Blueprints used mainly for UI, animations, and visual polish
- Modular design for reusability and scalability
- Uses Unreal’s **Component-based architecture** (`UInventoryComponent`, `UHealthComponent`, etc.)
- Designed for easy iteration and clean C++/Blueprint communication

---

## 🪶 Credits
Created by **MRJettie**  
Built for experience and portfolio growth through hands-on Unreal Engine C++ development.  
The project will be released as a **free game on Steam**.

---

## 📎 Repository Information
**License:** Free to use for learning/reference (no commercial redistribution)  
**Contributions:** Just me 
**Engine Version:** Unreal Engine 5.4  
**Language:** C++ / Unreal Gameplay Framework  
