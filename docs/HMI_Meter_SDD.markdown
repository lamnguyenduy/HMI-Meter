# Software Design Document (SDD) for HMI Meter System

## 1. Introduction
### 1.1 Purpose
This SDD describes the software architecture of the HMI Meter system, simulated on a Windows PC using Qt/C++, to display vehicle parameters (speed, fuel level, engine temperature, warnings). The architecture follows the MVC pattern, ensuring separation of concerns, compliance with MISRA C++, ISO 26262 ASIL-A, and ASPICE SWE.2.

### 1.2 Scope
- Implements SRS requirements: Display speed (0–200 km/h), fuel level (0–100%), engine temperature (0–150°C), warnings (engine fault, low fuel, high temperature).
- User-friendly interface, response time <100ms, optimized for 7-inch TFT (800x480).
- Developed in 30 hours (24/07/2025–26/07/2025) by a single developer.

### 2. System Architecture
### 2.1 Overview
The HMI Meter system uses the **MVC** pattern:
- **Model**: Manages data (speed, fuel, temperature, warnings) from CSV or random functions.
- **View**: Displays data on a simulated TFT interface using Qt widgets.
- **Controller**: Coordinates data updates every 100ms, ensuring response time <100ms.

### 2.2 Components
#### 2.2.1 Model (VehicleData)
- **Class**: `VehicleData`
- **Attributes**:
  - `speed: float` (0–200 km/h)
  - `fuelLevel: float` (0–100%)
  - `engineTemp: float` (0–150°C)
  - `engineFault: bool`
  - `lowFuelWarning: bool` (fuel <10%)
  - `highTempWarning: bool` (temperature >120°C)
- **Methods**:
  - `updateData()`: Reads CSV or random data, updates attributes.
  - `validateData()`: Ensures valid ranges (e.g., speed = max(0, min(200, speed))).
  - Getters: `getSpeed()`, `getFuelLevel()`, `getEngineTemp()`, `getWarnings()`.
- **Compliance**:
  - MISRA: Initialize all variables, use `std::unique_ptr`.
  - ISO 26262 ASIL-A: Validate abnormal inputs.

#### 2.2.2 View (HMIDisplay)
- **Class**: `HMIDisplay`
- **Attributes**:
  - `speedLabel: QLabel` (displays speed, 24px font).
  - `fuelBar: QProgressBar` (fuel level, 100px width).
  - `tempBar: QProgressBar` (engine temperature, 100px width).
  - `warningIcons: QLabel` (red/yellow icons, 32x32px).
- **Methods**:
  - `updateDisplay()`: Updates widgets with data from Controller.
  - `setLayout()`: Arranges widgets (speed 50% screen, fuel/temp bars, warning icons).
- **Compliance**:
  - MISRA: Initialize all widgets.
  - ISO 26262 ASIL-A: Ensure no crashes on invalid data.

#### 2.2.3 Controller (HMIController)
- **Class**: `HMIController`
- **Attributes**:
  - `model: std::unique_ptr<VehicleData>`
  - `view: std::unique_ptr<HMIDisplay>`
  - `timer: QTimer` (100ms interval)
- **Methods**:
  - `start()`: Starts timer for periodic updates.
  - `update()`: Fetches data from Model, checks warnings, updates View.
- **Compliance**:
  - MISRA: Single exit point per function, avoid infinite loops.
  - ISO 26262 ASIL-A: Response time <100ms.

### 3. Data Flow
- **Input**: Simulated data (CSV or random) → `VehicleData`.
- **Processing**: `HMIController` fetches data, checks warnings (fuel <10%, temp >120°C), sends to `HMIDisplay`.
- **Output**: Display on simulated TFT (800x480) with speed, fuel, temperature, warnings.

### 4. Diagrams
- **Class Diagram**: Stored in `docs/HMI_Meter_ClassDiagram.png`.
- **Data Flow Diagram (DFD)**: Stored in `docs/HMI_Meter_DFD.png`.

### 5. Implementation Notes
- **Tools**: Qt/C++, Qt Creator, CSV for simulated data.
- **Environment**: Windows PC, simulated TFT (800x480).
- **Standards**:
  - MISRA: Use Cppcheck for static analysis.
  - ISO 26262 ASIL-A: Unit testing (70% coverage) with Google Test.
  - ASPICE SWE.2: Documented architecture, traceable to SRS.

### 6. References
- SRS: `docs/HMI_Meter_SRS.md`
- MISRA C++:2008 Guidelines
- ISO 26262:2018 (Part 6, 8)
- Qt Documentation (doc.qt.io)