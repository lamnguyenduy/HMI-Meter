# Software Requirement Specification (SRS) for HMI Meter System

## 1. Introduction
### 1.1 Purpose
This SRS defines the functional and non-functional requirements for the HMI Meter system, a Human-Machine Interface for displaying critical vehicle information in an automotive context. The system will be developed and simulated on a Windows PC, targeting a TFT display emulation (7-inch, 800x480 resolution). The system displays key parameters (speed, fuel level, engine temperature, and warnings) and adheres to basic Automotive standards (MISRA C++, ISO 26262 ASIL-A).

### 1.2 Scope
The HMI Meter system will:
- Display vehicle speed, fuel level, engine temperature, and warnings (e.g., engine fault, low fuel, high temperature).
- Operate in a simulated environment on a Windows PC using Qt framework and C++.
- Ensure a user-friendly interface, response time under 100ms, and optimization for a small TFT display.
- Comply with MISRA C++ guidelines for safe coding and ISO 26262 ASIL-A for functional safety.
- Be developed within 30 hours by a single developer, focusing on core functionality without hardware integration.

### 1.3 Definitions, Acronyms, and Abbreviations
- **HMI**: Human-Machine Interface
- **TFT**: Thin-Film Transistor (display type)
- **MISRA**: Motor Industry Software Reliability Association
- **ISO 26262**: Functional safety standard for automotive systems
- **ASIL-A**: Automotive Safety Integrity Level A (lowest safety level)
- **SRS**: Software Requirement Specification
- **Qt**: Cross-platform framework for GUI development
- **MVC**: Model-View-Controller architecture

### 2. Overall Description
### 2.1 System Perspective
The HMI Meter is a standalone software system running on a Windows PC, simulating a vehicle dashboard. It uses simulated data (e.g., from CSV files or random functions) to display key vehicle parameters. The system follows the MVC architecture, with:
- **Model**: Processes input data (speed, fuel, temperature, warnings).
- **View**: Renders the GUI (speed gauge, fuel bar, temperature bar, warning icons).
- **Controller**: Updates the View based on Model data every 100ms.

### 2.2 User Characteristics
- **Primary User**: The driver (simulated in this context), who views the HMI Meter for vehicle status.
- **Developer**: The PM/developer, responsible for designing, coding, testing, and deploying the system.
- No direct user interaction (e.g., button clicks) is required, as the system only displays data.

### 2.3 Operating Environment
- **Platform**: Windows PC (Windows 10/11, 64-bit).
- **Development Tools**: Qt Creator (IDE), C++ (language), Figma (UI mockup), Google Test (unit testing), Git (version control).
- **Simulation**: Emulates a 7-inch TFT display (800x480 resolution) using Qt's rendering capabilities.
- **Constraints**: No hardware integration; data is simulated via CSV files or random functions.

### 2.4 Design and Implementation Constraints
- **Time**: 30 hours for development (24/07/2025 to 26/07/2025, 8-10 hours/day).
- **Personnel**: Single developer (PM/developer).
- **Standards**: MISRA C++ for safe coding, ISO 26262 ASIL-A for functional safety.
- **Resources**: Limited to lightweight tools (Qt, Cppcheck) to ensure low CPU/RAM usage.

### 3. Functional Requirements
#### 3.1 Speed Display
- **Description**: Display vehicle speed in km/h.
- **Input**: Simulated data (0–200 km/h, from CSV or random function).
- **Output**: Analog gauge (needle) or digital number (user-configurable).
- **Behavior**:
  - Update every 100ms.
  - Display 0 km/h for invalid inputs (e.g., negative values).
- **Test Scenarios**:
  - Input: 0, 100, 200, -10 km/h → Expected: Display 0, 100, 200, 0 km/h.
  - Verify update frequency (100ms).

#### 3.2 Fuel Level Display
- **Description**: Display fuel level as a percentage.
- **Input**: Simulated data (0–100%, from CSV or random function).
- **Output**: Horizontal bar or percentage number.
- **Behavior**:
  - Update every 100ms.
  - Show warning icon (red) when fuel level <10%.
- **Test Scenarios**:
  - Input: 100%, 50%, 5% → Expected: Display bar/number, warning icon for 5%.
  - Verify warning icon visibility and update frequency.

#### 3.3 Engine Temperature Display
- **Description**: Display engine temperature in °C.
- **Input**: Simulated data (0–150°C, from CSV or random function).
- **Output**: Horizontal bar or number.
- **Behavior**:
  - Update every 100ms.
  - Show warning icon (red) when temperature >120°C.
- **Test Scenarios**:
  - Input: 0, 100, 130°C → Expected: Display bar/number, warning icon for 130°C.
  - Verify update frequency.

#### 3.4 Warning Display
- **Description**: Display warnings for critical conditions (engine fault, low fuel, high temperature).
- **Input**: Simulated data (boolean for engine fault, thresholds for fuel <10%, temperature >120°C).
- **Output**: Red/yellow icons or text (e.g., "Engine Error").
- **Behavior**:
  - Update every 100ms.
  - Display warning immediately when condition is met.
- **Test Scenarios**:
  - Input: Engine fault = true → Expected: Display red "Engine Error" icon.
  - Input: Fuel = 5%, Temperature = 130°C → Expected: Display low fuel and high temperature icons.

### 4. Non-Functional Requirements
#### 4.1 User-Friendly Interface
- **Description**: The interface must be intuitive and minimize driver distraction.
- **Requirements**:
  - Font: Sans-serif (e.g., Arial), minimum 16px for readability.
  - Colors: High contrast (white/green on black background) for day/night visibility.
  - Layout: Speed (50% screen), fuel/temperature bars (small), warning icons (prominent, red/yellow).
- **Test Scenarios**:
  - Verify text readability on 800x480 resolution.
  - Confirm color contrast and icon visibility in simulated day/night modes.

#### 4.2 Response Time
- **Description**: The system must update display within 100ms of receiving new data.
- **Requirements**:
  - Data processing and rendering: <100ms (measured via Qt Creator profiling).
  - No lag or freeze during rapid data changes (e.g., speed 0–200 km/h in 1s).
- **Test Scenarios**:
  - Measure update time for speed, fuel, temperature, warnings (<100ms).
  - Test with rapid data changes (e.g., speed 0–200 km/h).

#### 4.3 Optimization for Small TFT Display
- **Description**: The interface must be optimized for a 7-inch TFT display (800x480).
- **Requirements**:
  - Resolution: Clear display at 800x480.
  - Resource Usage: CPU/RAM <50% on Windows PC (measured via Task Manager).
  - Layout: Simple, with up to 4 parameters (speed, fuel, temperature, warnings).
- **Test Scenarios**:
  - Verify display clarity on 800x480 emulation.
  - Measure CPU/RAM usage during continuous operation.

#### 4.4 Compliance with Standards
- **MISRA C++**:
  - Initialize all variables (Rule 6-2-1).
  - Avoid raw pointers; use smart pointers (Rule 5-0-1).
  - Single exit point per function (Rule 8-5-1).
- **ISO 26262 ASIL-A**:
  - Document requirements in SRS.
  - Perform unit testing (70% code coverage) using Google Test.
  - Store code and documentation in Git for configuration management.
- **Test Scenarios**:
  - Use Cppcheck to verify MISRA compliance.
  - Test abnormal inputs (e.g., speed = -10 km/h, fuel >100%) to ensure no crashes.

### 5. Test Scenarios
- **Speed**:
  - Input: 0, 100, 200, -10 km/h → Expected: Display 0, 100, 200, 0 km/h.
  - Verify: Update <100ms, readable font/icon.
- **Fuel Level**:
  - Input: 100%, 50%, 5% → Expected: Display bar/number, red warning icon at 5%.
  - Verify: Update <100ms, clear layout.
- **Engine Temperature**:
  - Input: 0, 100, 130°C → Expected: Display bar/number, red warning icon at 130°C.
  - Verify: Update <100ms, high contrast.
- **Warnings**:
  - Input: Engine fault = true, fuel = 5%, temperature = 130°C → Expected: Display all warning icons.
  - Verify: Immediate display, no overlap with other parameters.
- **Performance**:
  - Measure: Response time <100ms, CPU/RAM <50% on Windows PC.
  - Verify: No crashes during 1-hour continuous operation.

### 6. Assumptions and Constraints
- **Assumptions**:
  - Simulated data is provided via CSV files or random functions.
  - Windows PC has Qt Creator, C++ compiler, and sufficient resources (4GB RAM, 2GHz CPU).
- **Constraints**:
  - 30-hour development time (24/07/2025–26/07/2025).
  - Single developer, no hardware integration.
  - Limited to lightweight tools (Qt, Cppcheck, Google Test).

### 7. Deliverables
- **HMI Meter Software**: Simulated application running on Windows PC, displaying speed, fuel, temperature, and warnings.
- **Documentation**: SRS (this document), SDD (design document), test report.
- **Source Code**: C++ code, stored in Git, compliant with MISRA and ASIL-A.
- **Mockup**: UI mockup created in Figma.

### 8. References
- MISRA C++:2008 Guidelines (misra.org.uk).
- ISO 26262:2018, Part 6 and Part 8 (ASIL-A requirements).
- Qt Documentation (doc.qt.io).
- Google Test Documentation (github.com/google/googletest).