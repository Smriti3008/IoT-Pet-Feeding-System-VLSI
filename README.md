# IoT-Enabled Automated Pet Feeding System 🐾

> A smart pet feeding system combining IoT-based embedded implementation with VLSI-based logic simulation for reliable, automated pet care.

**Bangalore Institute of Technology | Major Project 2025-26**  
**Domain:** IoT & VLSI Design and Technology  
**Tools:** ESP32, Cadence Virtuoso, Verilog HDL, Arduino IDE, Telegram Bot API

---

## 📌 Overview

This project presents an **IoT-Enabled Automated Pet Feeding System** that ensures timely and accurate feeding despite busy schedules. It combines:

- **IoT Subsystem** — ESP32-based hardware for real-time feeding automation
- **VLSI Subsystem** — Verilog HDL feeding timer verified using Cadence tools

The system detects pet presence, dispenses food, measures quantity, supplies water, and sends real-time Telegram notifications to the owner.

---

## 🏗️ System Architecture

```
                    ┌─────────────────────────────────┐
                    │         ESP32 (Central MCU)      │
                    └────────────────┬────────────────┘
                                     │
          ┌──────────┬───────────────┼───────────────┬──────────┐
          │          │               │               │          │
     IR Sensor  Load Cell        DC Motor       Water Pump   LCD
     (Pet        + HX711          + Driver      (Relay)    Display
    Detection)  (Weight)         (Food)         (Water)
                                                              │
                                                        Telegram Bot
                                                        (Notifications)

    VLSI Subsystem:
    Feeding Timer Module → Verilog HDL → Cadence Simulation
    → Area / Power / Timing Reports
```

---

## ⚙️ Hardware Components

| Component | Function |
|-----------|----------|
| ESP32 Microcontroller | Central control + Wi-Fi communication |
| IR Sensor | Detects pet presence at feeding area |
| Load Cell + HX711 | Measures food weight accurately |
| DC Motor + Driver | Operates food dispensing mechanism |
| Water Pump (Relay) | Supplies water after feeding |
| LCD Display | Shows timer, weight, and system status |
| Buzzer | Alerts at feeding time |
| Telegram Bot API | Sends real-time mobile notifications |

---

## 💻 VLSI Design

A **Feeding Timer Module** was designed in Verilog HDL and verified using Cadence tools.

### Design Flow:
1. Requirement Specification (clock frequency, feeding interval)
2. RTL Modeling in Verilog HDL
3. Testbench Development
4. Functional Simulation (Cadence)
5. Synthesis → Area, Power, Timing Reports
6. Verification & Validation

### Synthesis Results:

| Parameter | Value |
|-----------|-------|
| Total Cell Count | 25 gates |
| Total Area | 247.506 µm² |
| Sequential Cells | 7 (70.06% area) |
| Logic Gates | 16 (27.5% area) |
| Power Consumption | ≈ 4.2 µW |
| Critical Path Delay | 867 ps |
| Timing Slack | +6933 ps ✅ |
| Tool | Cadence Genus 21.14 |

---

## 🔄 System Working Flow

```
Power ON → ESP32 Initializes → Timer Starts
              ↓
         Timer Triggers → Buzzer ON
              ↓
         IR Sensor → Pet Detected?
         YES → Food Dispensing (DC Motor)
         NO  → Telegram: "Pet Missed Food" 🐾
              ↓
         Load Cell → Measures food weight
              ↓
         Water Pump → Water dispensed
              ↓
         Telegram Notification → "Feeding Complete ✅"
              ↓
         Timer Reset → Next Cycle
```

---

## 📊 Results

### IoT Results
- ✅ IR sensor showed stable detection with no false triggers
- ✅ DC motor dispensed consistent food portions across test runs
- ✅ Load cell maintained accurate weight readings (negligible drift)
- ✅ Water pump operated reliably with relay-based control
- ✅ Telegram notifications delivered instantly during all feeding stages

### VLSI Results Comparison

| Parameter | IoT Control | VLSI Timer Logic |
|-----------|-------------|-----------------|
| Timing Control | Software-based | Hardware clock-driven |
| Power | High (MCU + Wi-Fi) | Very low (≈ 4.2 µW) |
| Area Efficiency | Not optimized | Highly optimized |
| Critical Path | Variable | 867 ps |
| Timing Reliability | CPU-dependent | Deterministic |

---

## 🛠️ Tools & Technologies

- **Microcontroller:** ESP32
- **IDE:** Arduino IDE
- **HDL:** Verilog HDL
- **VLSI Tool:** Cadence (Virtuoso, Genus Synthesis)
- **Simulation:** Cadence SimVision
- **Notification:** Telegram Bot API
- **University:** Bangalore Institute of Technology (VTU)

---

## 📁 Repository Contents

| File | Description |
|------|-------------|
| `Pet_feeder_project.pdf` | Complete project report |
| `pet_feeding_system_final_phase_ppt.pptx` | Project presentation |
| `Major_pro_front_sheet_final.pdf` | Project certificate |

---

## 🔮 Future Work

1. Implement feeding timer on actual FPGA hardware
2. Develop dedicated mobile app for scheduling & analytics
3. Add camera module for pet identification
4. Integrate solar power for outdoor use
5. Support multiple pets with individual feeding profiles
6. Full ASIC implementation of control logic

---

## 👩‍💻 Authors

**Smriti Subramaniam** (1BI22VL047)  
**Thanishqka P** (1BI22VL051)

- 🎓 B.E. Electronics Engineering (VLSI Design & Technology)
- 🏫 Bangalore Institute of Technology, Bangalore
- 📧 theppss3006@gmail.com
- 🔗 [GitHub](https://github.com/Smriti3008)

**Guide:** Mrs. Lavanya Y S, Asst. Professor, Dept. of EE(VDT), BIT

---

## 📄 License

This project was developed for academic purposes at Bangalore Institute of Technology under Visvesvaraya Technological University (VTU), 2025-26.
