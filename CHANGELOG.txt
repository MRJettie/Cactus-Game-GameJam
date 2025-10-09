# 📜 Changelog

All notable changes to this project will be documented in this file.  
The format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),  
and this project roughly adheres to [Semantic Versioning](https://semver.org/).

---

## [Unreleased]
### Planned
- Implement enemy spawning and basic combat interaction  
- Integrate HealthComponent damage system with enemy actors  
- Add loot drops (coins, XP, and resource multipliers)  
- Expand vendor and skill point systems for upgrades and scaling  
- Add healing and damage resistance functionality to HealthComponent  
- General polish and performance optimization for release build  

---

## [v0.2.0] – 2025-10-08
### Added
- Implemented **BaseWeapon class** and **two child weapon classes**  
- Created **UI elements** that update based on the equipped weapon  
- Added **HealthComponent** for reusable health and damage logic (shared by player and enemies)  
- Added **InventoryComponent** for tracking coins, XP, and resources  
- Added **BabyCactus configuration** that progresses based on collected resources  

### Changed
- Simplified pickup system — removed individual item types like *Sunlight* and *Water*  
- Each **BasePickup child class** now acts as a **multiplier** (e.g., +1 Water, +5 Water)  
- Updated BabyCactus progression and inventory logic to support the new pickup system  
- Linked weapon equip and pickup logic to the UI  

### Known Issues
- Weapon switching and UI state desync during swaps  
- Secondary weapon **does not properly display its ammo count** when switched to,  
  though the weapon name updates correctly in the UI  
- Weapons **disappear after switching twice** during testing  
- Enemy health and damage interaction not yet active  

---

## [v0.1.0] – 2025-09-20
### Added
- Initial Unreal Engine 5.4 project setup  
- **BabyCactus actor** and early progression system experiments  
- Early **child pickup classes** (Water, Sunlight, etc.)  
- Attempted resource-based progression logic  
- Initial groundwork for **InventoryComponent** and **HealthComponent**  

### Known Issues
- Separate item types (Sunlight, Water, etc.) caused inconsistent progression logic  
- Cactus growth and resource tracking were unstable  
- No weapon system or UI present yet  
