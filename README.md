# Inventory Management 库存管理

## Features 功能

> Usage Sample 使用示例: [docs/usage_sample.md](docs/usage_sample.md)

- Inventory Management 库存管理
    - Inbound Items 商品入库
    - Outbound Items 商品出库
- In/outbound Log Query 入库出库记录查询
    - Search Item Name by Keyword 搜索商品名称关键词
    - Display Certain Category Logs Only 仅显示某个分类的记录
- User Login/Adding 用户登录/新建

## Data Dictionary 数据字典

> Corresponding lengths defined in [const.h](const.h). 相应长度定义于 [const.h](const.h)。

### Inventory Table 库存表


| Field 数据域 | Type 类型 | Meaning 含义           | Other 其他       |
| ------------ | --------- | ---------------------- | ---------------- |
| `name`       | char(16)  | Item Name 商品名称     | Primary Key 主码 |
| `cate`       | char(16)  | Item Category 商品分类 |
| `amount`     | int       | Item Amount 商品数量   |

### In/outbound Table 入库出库表

| Field 数据域 | Type 类型 | Meaning 含义           | Other 其他       |
| ------------ | --------- | ---------------------- | ---------------- |
| `name`       | char(16)  | Item Name 商品名称     |
| `cate`       | char(16)  | Item Category 商品分类 |
| `amount`     | int       | I/O Amount 出入数量    |
| `time`       | char(20)  | I/O time 出入时间      | Primary Key 主码 |

> Known issue: When multiple I/O manipulation occur in same second, only the first log will be recorded.
>
> 已知问题：当多个入库/出库操作在同一秒内发生，只有第一条日志将被记录。

### Users Table 用户表

| Field 数据域 | Type 类型 | Meaning 含义     | Other 其他       |
| ------------ | --------- | ---------------- | ---------------- |
| `name`       | char(16)  | User Name 用户名 | Primary Key 主码 |
| `pswd`       | char(16)  | Password 密码    |

## Development Environment 开发环境

- Operating System: Arch Linux x86_64 (4.20.0-arch1-1-ARCH)
- QT: qt5-base 5.12.0-2
- SQL: sqlite 3.26.0-1
- IDE: qtcreator 4.8.0-2
- Editor: vscodium-bin 1.30.2-4
