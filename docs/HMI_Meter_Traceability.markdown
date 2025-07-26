# Traceability Matrix for HMI Meter System

## 1. Purpose
This document provides traceability between the Data Flow Diagram (DFD) and the Software Requirement Specification (SRS) for the HMI Meter system, ensuring that all requirements are addressed in the design. It complies with ASPICE SYS.2, SWE.1, SWE.2, and ISO 26262 ASIL-A.

## 2. Traceability Matrix

| SRS ID | Requirement Description | DFD Component/Luồng Dữ Liệu | Notes |
|--------|-------------------------|-----------------------------|-------|
| **FUN-001** | Hiển thị tốc độ xe (0–200 km/h, cập nhật <100ms). | - **VehicleData**: Đọc và kiểm tra dữ liệu tốc độ từ Data Source (Raw Data).<br>- **HMIController**: Lấy tốc độ từ VehicleData (Validated Data), gửi đến HMIDisplay mỗi 100ms.<br>- **HMIDisplay**: Hiển thị tốc độ trên giao diện (Display Data).<br>- **TFT Display**: Render tốc độ (Rendered Interface). | - Tốc độ được hiển thị dưới dạng số digital (font 48px).<br>- Đảm bảo phản hồi <100ms bằng QTimer. |
| **FUN-002** | Hiển thị mức nhiên liệu (0–100%, cảnh báo <10%). | - **VehicleData**: Đọc dữ liệu nhiên liệu, kiểm tra ngưỡng <10% (Raw Data → Validated Data).<br>- **HMIController**: Xử lý cảnh báo nhiên liệu thấp, gửi đến HMIDisplay.<br>- **HMIDisplay**: Hiển thị thanh nhiên liệu và icon cảnh báo vàng.<br>- **TFT Display**: Render thanh và icon. | - Thanh ngang (QProgressBar, 130x20px).<br>- Cảnh báo vàng (#FFCA28) khi <10%. |
| **FUN-003** | Hiển thị nhiệt độ động cơ (0–150°C, cảnh báo >120°C). | - **VehicleData**: Đọc dữ liệu nhiệt độ, kiểm tra ngưỡng >120°C.<br>- **HMIController**: Xử lý cảnh báo nhiệt độ cao, gửi đến HMIDisplay.<br>- **HMIDisplay**: Hiển thị thanh nhiệt độ và icon cảnh báo đỏ.<br>- **TFT Display**: Render thanh và icon. | - Thanh ngang (QProgressBar, 130x20px).<br>- Cảnh báo đỏ (#F44336) khi >120°C. |
| **FUN-004** | Hiển thị cảnh báo lỗi động cơ (boolean). | - **VehicleData**: Đọc dữ liệu lỗi động cơ (Raw Data).<br>- **HMIController**: Gửi trạng thái lỗi đến HMIDisplay.<br>- **HMIDisplay**: Hiển thị icon cảnh báo đỏ.<br>- **TFT Display**: Render icon. | - Icon 32x32px, đỏ (#F44336). |
| **NFUN-001** | Giao diện thân thiện (font ≥16px, tương phản cao). | - **HMIDisplay**: Sử dụng font Arial ≥16px, màu trắng/xanh trên nền đen.<br>- **TFT Display**: Render giao diện 800x480px. | - Font tốc độ 48px, nhãn 16–20px.<br>- Nền đen (#0F1017), chữ trắng (#FFFFFF). |
| **NFUN-002** | Phản hồi giao diện <100ms. | - **HMIController**: Cập nhật dữ liệu mỗi 100ms bằng QTimer.<br>- **HMIDisplay**: Xử lý Display Data nhanh chóng.<br>- **TFT Display**: Render không bị lag. | - Đo hiệu suất bằng Qt Creator profiling.<br>- CPU/RAM <50% (Windows Task Manager). |
| **NFUN-003** | Tối ưu cho màn hình TFT 7 inch (800x480). | - **HMIDisplay**: Bố cục tốc độ chiếm 50%, thanh nhiên liệu/nhiệt độ nhỏ gọn.<br>- **TFT Display**: Render đúng độ phân giải 800x480px. | - Kiểm tra giao diện trên Qt Creator (QSize(800, 480)). |

## 3. References
- SRS: `docs/HMI_Meter_SRS.md`
- DFD: `docs/HMI_Meter_DFD.png`
- SDD: `docs/HMI_Meter_SDD.md`