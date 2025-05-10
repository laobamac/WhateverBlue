WhateverBlue
=============

[![构建状态](https://github.com/acidanthera/WhateverBlue/actions/workflows/main.yml/badge.svg?branch=master)](https://github.com/acidanthera/WhateverBlue/actions) [![扫描状态](https://scan.coverity.com/projects/16177/badge.svg?flat=1)](https://scan.coverity.com/projects/16177)

[Lilu](https://github.com/acidanthera/Lilu) 插件，用于在 macOS 上为特定 GPU 提供补丁。需要 Lilu 1.5.6 或更高版本。

#### 功能

- 修复因部分笔记本电脑的 Intel IGPU 报告无效 DPCD 链路速率导致的内核崩溃。
- 修复 Skylake、Kaby Lake 和 Coffee Lake 平台在高像素时钟率下建立 Intel HDMI 连接时的无限循环问题。
- 在 Kaby Lake 及更新平台上强制对非内置显示器执行完整模式设置，以解决启动黑屏问题。
- 修复 Intel Kaby Lake 及更新平台的视频播放卡顿问题。
- 为 Intel KBL 和 CFL 平台上罕见的强制唤醒超时崩溃提供临时解决方案。
- 支持 Intel ICL 平台所有有效的核心显示时钟（CDCLK）频率。
- 修复因 Intel ICL 平台错误计算 DVMT 预分配内存导致的内核崩溃。

#### 文档

请阅读 [常见问题解答](./Manual/)，避免提问。目前暂不提供技术支持。

#### 启动参数

##### 全局参数

| 启动参数       | 设备属性（DeviceProperties） | 描述                                                                 |
|----------------|-----------------------------|----------------------------------------------------------------------|
| `-webbeta`     | 无                          | 在不受支持的 macOS 版本（默认启用 15 及以下版本）上启用 WhateverBlue |
| `-webdbg`      | 无                          | 启用调试输出（仅在 DEBUG 版本中可用）                                 |
| `-weboff`      | 无                          | 禁用 WhateverBlue                                                   |

##### 切换 GPU

| 启动参数          | 设备属性（DeviceProperties）                 | 描述                                     |
|-------------------|---------------------------------------------|------------------------------------------|
| `-webnoegpu`      | 为每个 GFX0 添加 `disable-gpu` 属性          | 禁用所有外置 GPU                         |
| `-webnoigpu`      | 为 IGPU 添加 `disable-gpu` 属性              | 禁用内置 GPU                             |
| `-webswitchgpu`   | 为 IGPU 添加 `switch-to-external-gpu` 属性   | 当外置 GPU 存在时禁用内置 GPU            |

##### Board-id 相关

| 启动参数           | 设备属性（DeviceProperties）                 | 描述                                                                 |
|--------------------|---------------------------------------------|----------------------------------------------------------------------|
| `agdpmod=ignore`   | 为外置 GPU 添加 `agdpmod` 属性              | 禁用 AGDP 补丁（外置 GPU 默认隐式值为 `vit9696,pikera`）             |
| `agdpmod=pikera`   | 为外置 GPU 添加 `agdpmod` 属性              | 将 `board-id` 替换为 `board-ix`                                      |
| `agdpmod=vit9696`  | 为外置 GPU 添加 `agdpmod` 属性              | 禁用对 `board-id` 的检查                                             |

##### Intel HD 显卡

| 启动参数                | 设备属性（DeviceProperties）                              | 描述                                                                 |
|-------------------------|----------------------------------------------------------|----------------------------------------------------------------------|
| `-igfxblr`              | 为 IGPU 添加 `enable-backlight-registers-fix` 属性        | 修复 KBL、CFL 和 ICL 平台的背光寄存器                                |
| `-igfxbls`              | 为 IGPU 添加 `enable-backlight-smoother` 属性             | 在 IVB+ 平台上使亮度过渡更平滑。[阅读手册](./Manual/FAQ.IntelHD.en.md#customize-the-behavior-of-the-backlight-smoother-to-improve-your-experience) |
| `-igfxblt`              | 为 IGPU 添加 `enable-backlight-registers-alternative-fix` 属性 | Backlight Registers Fix 的替代方案，支持在 macOS 13.4 或更高版本的 KBL/CFL 平台上启用 Backlight Smoother。[阅读手册](./Manual/FAQ.IntelHD.en.md#fix-the-3-minute-black-screen-issue-on-cfl-platforms-running-macos-134-or-later) |
| `-igfxcdc`              | 为 IGPU 添加 `enable-cdclk-frequency-fix` 属性            | 支持 ICL 平台所有有效的核心显示时钟（CDCLK）频率。[阅读手册](./Manual/FAQ.IntelHD.en.md#support-all-possible-core-display-clock-cdclk-frequencies-on-icl-platforms) |
| `-igfxdbeo`             | 为 IGPU 添加 `enable-dbuf-early-optimizer` 属性           | 修复 ICL+ 平台的显示数据缓冲区（DBUF）问题。[阅读手册](./Manual/FAQ.IntelHD.en.md#fix-the-issue-that-the-builtin-display-remains-garbled-after-the-system-boots-on-icl-platforms) |
| `-igfxdump`             | 无                                                       | 将 IGPU 帧缓冲区驱动转储到 `/var/log/AppleIntelFramebuffer_X_Y`（仅 DEBUG 版本可用） |
| `-igfxdvmt`             | 为 IGPU 添加 `enable-dvmt-calc-fix` 属性                  | 修复 Intel ICL 平台因错误计算 DVMT 预分配内存导致的内核崩溃          |
| `-igfxfbdump`           | 无                                                       | 将原生和补丁后的帧缓冲区表转储到 IOReg 的 `IOService:/IOResources/WhateverBlue` |
| `-igfxhdmidivs`         | 为 IGPU 添加 `enable-hdmi-dividers-fix` 属性              | 修复 SKL、KBL 和 CFL 平台在高像素时钟率下建立 HDMI 连接的无限循环问题 |
| `-igfxi2cdbg`           | 无                                                       | 在 I2C-over-AUX 事务中启用详细输出（仅调试用途）                     |
| `-igfxlspcon`           | 为 IGPU 添加 `enable-lspcon-support` 属性                 | 启用对板载 LSPCON 芯片的支持。[阅读手册](./Manual/FAQ.IntelHD.en.md#lspcon-driver-support-to-enable-displayport-to-hdmi-20-output-on-igpu) |
| `-igfxmlr`              | 为 IGPU 添加 `enable-dpcd-max-link-rate-fix` 属性         | 应用最大链路速率修复                                                 |
| `-igfxmpc`              | 为 IGPU 添加 `enable-max-pixel-clock-override` 和 `max-pixel-clock-frequency` 属性 | 提高最大像素时钟（替代修改 `CoreDisplay.framework`）                 |
| `-igfxnohdmi`           | 为 IGPU 添加 `disable-hdmi-patches` 属性                  | 禁用 DP 转 HDMI 的数字音频补丁                                       |
| `-igfxnotelemetryload`  | 为 IGPU 添加 `disable-telemetry-load` 属性                | 禁用可能导致部分笔记本（如 Chromebook）启动冻结的 iGPU 遥测加载      |
| `-igfxsklaskbl`         | 无                                                       | 强制在 Skylake 机型上加载 Kaby Lake（KBL）显卡驱动（需 KBL 的 `device-id` 和 `ig-platform-id`，macOS 13+ 无需此参数） |
| `-igfxtypec`            | 无                                                       | 强制为 Type-C 平台启用 DP 连接                                       |
| `-igfxvesa`             | 无                                                       | 禁用 Intel 显卡硬件加速                                              |
| `igfxagdc=0`            | 为 IGPU 添加 `disable-agdc` 属性                         | 禁用 AGDC                                                            |
| `igfxfcms=1`            | 为 IGPU 添加 `complete-modeset` 属性                     | 在 Skylake 或 Apple 固件上强制完整模式设置                          |
| `igfxfcmsfbs=`          | 为 IGPU 添加 `complete-modeset-framebuffers` 属性         | 指定需强制完整模式设置的连接器索引（格式示例：`0x010203` 表示索引 1、2、3，`-1` 禁用） |
| `igfxframe=frame`       | 为 IGPU 注入 `AAPL,ig-platform-id` 或 `AAPL,snb-platform-id` 属性 | 强制注入特定帧缓冲区标识（仅测试用途）                               |
| `igfxfw=2`              | 为 IGPU 添加 `igfxfw` 属性                               | 强制加载 Apple GuC 固件                                              |
| `igfxgl=1`              | 为 IGPU 添加 `disable-metal` 属性                        | 禁用 Intel 的 Metal 支持                                             |
| `igfxmetal=1`           | 为 IGPU 添加 `enable-metal` 属性                         | 强制启用 Intel 的 Metal 支持（仅离线渲染）                           |
| `igfxonln=1`            | 为 IGPU 添加 `force-online` 属性                         | 强制所有显示器显示为在线状态                                         |
| `igfxonlnfbs=MASK`      | 为 IGPU 添加 `force-online-framebuffers` 属性             | 指定需强制在线状态的连接器索引（格式同 `igfxfcmsfbs`）               |
| `igfxpavp=1`            | 为 IGPU 添加 `igfxpavp` 属性                             | 强制启用 PAVP 输出                                                  |
| `igfxrpsc=1`            | 为 IGPU 添加 `rps-control` 属性                          | 启用 RPS 控制补丁（提升 IGPU 性能）                                 |
| `igfxsnb=0`             | 无                                                       | 禁用针对 Sandy Bridge CPU 的 IntelAccelerator 名称修复               |

##### 其他参数

| 启动参数       | 设备属性（DeviceProperties）     | 描述                             |
|----------------|---------------------------------|----------------------------------|
| `webtree=1`    | 添加 `rebuild-device-tree` 属性 | 强制在 Apple 固件上重建设备树    |

#### 致谢

- [Apple](https://www.apple.com) 提供 macOS
- [AMD](https://www.amd.com) 提供 ATOM VBIOS 解析代码
- [The PCI ID Repository](http://pci-ids.ucw.cz) 提供多款 GPU 型号名称
- [Andrey1970AppleLife](https://github.com/Andrey1970AppleLife) 编写[常见问题解答](./Manual/)
- [FireWolf](https://github.com/0xFireWolf/) 贡献了 DPCD 最大链路速率修复、Intel HDMI 无限循环修复、LSPCON 驱动支持、ICL 平台 CDCLK 频率修复、ICL 平台 DVMT 内存计算修复、IVB+ 平台背光平滑调节、ICL 平台 DBUF 修复及背光寄存器替代修复
- [Floris497](https://github.com/Floris497) 提供 CoreDisplay [补丁](https://github.com/Floris497/mac-pixel-clock-patch-v2)
- [Fraxul](https://github.com/Fraxul) 提供原始 CFL 背光补丁
- [headkaze](https://github.com/headkaze) 提供 Intel 帧缓冲区补丁代码及 CFL 背光补丁改进
- [hieplpvip](https://github.com/hieplpvip) 开发初始 AppleBacklight 补丁插件
- [igork](https://applelife.ru/members/igork.564/) 发现电源门控补丁及多项 FP 研究
- [lvs1974](https://applelife.ru/members/lvs1974.53809) 持续贡献 Intel 和 NVIDIA 修复代码
- [mologie](https://github.com/mologie/NVWebDriverLibValFix) 开发 NVWebDriverLibValFix.kext，强制 macOS 识别 NVIDIA 网页驱动为平台二进制文件
- [PMheart](https://github.com/PMheart) 提供 CoreDisplay 补丁代码及 Intel 修复回传
- [RehabMan](https://github.com/RehabMan) 提供多项改进
- [RemB](https://applelife.ru/members/remb.8064/) 持续研究睡眠唤醒问题并发现 AMD 相关寄存器
- [Vandroiy](https://applelife.ru/members/vandroiy.83653/) 维护 GPU 型号检测数据库
- [YungRaj](https://github.com/YungRaj) 和 [syscl](https://github.com/syscl) 回传 Intel 修复
- [vit9696](https://github.com/vit9696) 编写并维护本项目
