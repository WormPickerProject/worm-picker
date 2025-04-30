# Worm Picker 2.0

> **Task-based motion control architecture for *C. elegans* manipulation**  
> Motion‑control architecture developed for Logan Kaising’s 2025 honors thesis, *Design and Implementation of a Motion Control Architecture for WormPicker 2.0 Robotic System* (Ohio State University, Knowledge Bank ID 36c98e2e‑396e‑464d‑a1c3‑0c970d31b80a).

[![ROS 2](https://img.shields.io/badge/ROS2-Humble-blue.svg?logo=ros)](https://docs.ros.org/en/humble/) 
[![MoveIt 2](https://img.shields.io/badge/MoveIt2-Humble-blueviolet.svg)](https://moveit.ros.org/) 
[![License: Custom](https://img.shields.io/badge/License-Custom%20Limited-orange.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C++-20-00599C.svg?logo=c%2B%2B)](https://en.cppreference.com/w/cpp/20)

WormPicker 2.0 is a layered, task‑centric robotics platform that automates plate‑based worm manipulation at **13 animals min⁻¹**—a four‑fold improvement over prior systems—while maintaining sub‑0.01 mm positioning accuracy.  It marries a Yaskawa GP4 industrial manipulator with ROS 2, MoveIt 2, and a purpose‑built motion‑control stack to eliminate the manual bottleneck in high‑throughput *C. elegans* genetics.

---

## Table of Contents
1. [Overview](#overview)
2. [Key Features](#key-features)
3. [Performance Highlights](#performance-highlights)
4. [System Requirements](#system-requirements)
5. [Repository Structure](#repository-structure)
6. [Installation](#installation)
7. [Usage](#usage)
8. [Citing WormPicker 2.0](#citing-wormpicker-20)
9. [Contribution Policy](#contribution-policy)
10. [License](#license)
11. [Contact](#contact)

---

## Overview
WormPicker 2.0 translates high‑level experimental commands into collision‑free trajectories through a five‑layer software architecture:

1. **Interface Layer** – CLI & TCP/IP command APIs.  
2. **Command Layer**  – Lightweight parser‑combinator library produces immutable `CommandInfo` objects.  
3. **Task Layer**     – Factory pattern expands commands into MoveIt Task Constructor (MTC) tasks comprising reusable motion stages.  
4. **Planning Layer** – Planner factory selects OMPL / Pilz / Cartesian planners and validates solutions against heuristics.  
5. **Execution Layer** – ROS 2 controllers stream trajectories to the GP4; feedback loops maintain gentle contact with agar.

A semi‑automated calibration node aligns digital models with the physical work‑cell, ensuring repeatability across up to 250 plates.

## Key Features

| Category | Highlights |
|----------|------------|
| **Task‑based architecture** | Declarative chain‑of‑stage design built on ROS 2 + MoveIt Task Constructor |
| **Rich motion primitives** | Joint, Cartesian, circular, and relative moves with per‑stage velocity/acceleration scaling |
| **Workstation & hotel maps** | JSON‑defined reference frames for plates, tools, and storage locations |

## Performance Highlights
* **Throughput**          13 worms min⁻¹ (×4 vs. WormPicker 1.0)  
* **Repeatability**       ± 0.01 mm (Yaskawa GP4 spec)  
* **Workspace**           250 standard 6 cm agar plates  
* **Runtime**             24/7 continuous operation

## System Requirements

| Category | Requirement |
|----------|-------------|
| **Operating System** | Ubuntu 22.04 LTS (tested) |
| **ROS 2** | Humble Hawksbill |
| **MoveIt 2** | Humble with Task Constructor |
| **Compiler** | GCC 11+ / Clang 15+ with C++20 support |
| **CMake** | 3.22 or newer |
| **Robot Hardware** | Yaskawa GP4 or any ROS 2-compatible 6+ DOF arm |
| **Dependencies** | Boost, fmt, yaml-cpp, nlohmann/json, tf2, Eigen3 |

## Repository Structure
```text
worm-picker/
├── worm_picker_core/              # Core libraries & nodes
│   ├── include/worm_picker_core/  # Public headers (core | infra | system | utils)
│   ├── src/                       # Implementation
│   └── config/                    # YAML params + launch files
├── worm_picker_custom_msgs/       # ROS 2 msg/srv definitions
├── worm_picker_description/       # URDF, meshes, semantic description
├── worm_picker_moveit_config/     # MoveIt 2 configuration package
├── dependencies.repos             # wstool / vcs import file
├── CONTRIBUTING.md                # Restricted contribution policy
├── LICENSE                        # Custom Limited License Agreement
└── README.md                      # This document
```

## Installation
*TO BE FILLED OUT LATER*

> **Quick reference**  
> Clone with `vcs import < dependencies.repos` · `colcon build --symlink-install` · source the workspace · launch `worm_picker_system.launch.py`.

## Usage
*TO BE FILLED OUT LATER*

## Citing WormPicker 2.0
If this software contributes to your academic work, please cite the associated thesis:

> Kaising, L. (2025). *Design and Implementation of a Motion Control Architecture for WormPicker 2.0 Robotic System.* The Ohio State University Knowledge Bank. <https://kb.osu.edu/items/36c98e2e-396e-464d-a1c3-0c970d31b80a>

## Contribution Policy
This repository is governed by a **restricted licence**.  Contributions are accepted **only** from authorised Fang‑Yen‑Lab personnel.  External pull requests will be closed without review.  See [CONTRIBUTING.md](CONTRIBUTING.md) for details.

## License
WormPicker 2.0 is released under a bespoke *Custom Limited License Agreement* that grants defined rights exclusively to the Fang‑Yen‑Lab.  Refer to the [LICENSE](LICENSE) file for legally binding terms.

## Contact

| Role | Name | E‑mail |
|------|------|--------|
| Original Author | Logan Kaising | <lkaising@outlook.com> |
| Lab Manager | Li (John) Zihao | <li.14075@osu.edu> |

---

© 2025 Logan Kaising. All rights reserved.