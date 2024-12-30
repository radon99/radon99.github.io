SANGHUN
*******************************************************************************
**            MyChip Station LayNet Pro 2017 
**            Copyright(c) 1992-2017 MyCAD, Inc. 
**            TIME = 15:34:31  DATE = 05/31/23 
*******************************************************************************
*'SANGHUN' LAYOUT CELL
*.GLOBAL VDD:P C2 C0 C1 O_CLK
*.GLOBAL D_CLK CLK GND:G
M1             2      11     VDD     VDD       PMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=2.27478P PD=3.27826U
M2             3      12     VDD     VDD       PMOS W=7.2U L=0.4U AS=7.92P PS=9.4U AD=6.82435P PD=9.83478U
M3           VDD      C0      21     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M4             4      11      21     VDD       PMOS W=2.4U L=0.4U AS=1.44P PS=1.2U AD=1.44P PD=1.2U
M5             4       2      C0     VDD       PMOS W=2.4U L=0.4U AS=1.44P PS=1.2U AD=2.64P PD=4.6U
M6           VDD       3      11     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M7           VDD      13      23     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M8           VDD     CLK      12     VDD       PMOS W=1.2U L=0.4U AS=1.13739P PS=1.63913U AD=1.32P PD=3.4U
M9           VDD      C1      24     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M10            5      13      24     VDD       PMOS W=2.4U L=0.4U AS=1.44P PS=1.2U AD=1.44P PD=1.2U
M11          VDD       3      45     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M12            5      23      C1     VDD       PMOS W=2.4U L=0.4U AS=1.44P PS=1.2U AD=2.64P PD=4.6U
M13           26     CLK      45     VDD       PMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.44P PD=1.2U
M14          VDD       5      48     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M15            7      14     VDD     VDD       PMOS W=7.2U L=0.4U AS=7.92P PS=9.4U AD=6.82435P PD=9.83478U
M16          VDD       4      48     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M17          VDD      48      27     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M18          VDD       7      13     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M19            6      27     VDD     VDD       PMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=2.27478P PD=3.27826U
M20          VDD       3      14     VDD       PMOS W=1.2U L=0.4U AS=1.13739P PS=1.63913U AD=1.32P PD=3.4U
M21          VDD       6      16     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M22          VDD       7      50     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M23          VDD       8      28     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M24           29       3      50     VDD       PMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.44P PD=1.2U
M25          VDD      28      30     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M26            8      15     VDD     VDD       PMOS W=7.2U L=0.4U AS=7.92P PS=9.4U AD=6.82435P PD=9.83478U
M27          VDD      30      31     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M28          VDD      31      32     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M29            9       8     VDD     VDD       PMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=2.27478P PD=3.27826U
M30          VDD      32      33     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M31          VDD      33      34     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M32          VDD       7      15     VDD       PMOS W=1.2U L=0.4U AS=1.13739P PS=1.63913U AD=1.32P PD=3.4U
M33          VDD      34      35     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M34          VDD       8      53     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M35          VDD      35   O_CLK     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M36           37       7      53     VDD       PMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.44P PD=1.2U
M37          VDD      C2      38     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M38          VDD      18      39     VDD       PMOS W=7.2U L=0.4U AS=6.82435P PS=9.83478U AD=7.92P PD=9.4U
M39          VDD      38      19     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M40          VDD       8      19     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M41          VDD      39   D_CLK     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=2.64P PD=4.6U
M42          VDD      C2      20     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M43          VDD      16      18     VDD       PMOS W=1.2U L=0.4U AS=1.13739P PS=1.63913U AD=1.32P PD=3.4U
M44          VDD       9      20     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M45          VDD      41      56     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M46          VDD      19      41     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
M47           42      16      56     VDD       PMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.44P PD=1.2U
M48          VDD      20      41     VDD       PMOS W=2.4U L=0.4U AS=2.27478P PS=3.27826U AD=1.44P PD=1.2U
*---------------------------------------------------
*	# OF MOSEF PMOS       : 48
*---------------------------------------------------
*
M49            2      11     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M50            3     CLK      43     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.56P PD=1.3U
M51           21      C0     GND     GND       NMOS W=1.2U L=0.4U AS=0.72P PS=1.2U AD=1.18P PD=2.00667U
M52           43      12     GND     GND       NMOS W=2.4U L=0.4U AS=1.56P PS=1.3U AD=2.36P PD=4.01333U
M53            4       2      21     GND       NMOS W=1.2U L=0.4U AS=0.72P PS=1.2U AD=0.72P PD=1.2U
M54            4      11      C0     GND       NMOS W=1.2U L=0.4U AS=0.72P PS=1.2U AD=1.32P PD=3.4U
M55           11       3     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M56           23      13     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M57           12      26      44     GND       NMOS W=4.8U L=0.4U AS=5.28P PS=7U AD=2.88P PD=1.2U
M58           24      C1     GND     GND       NMOS W=1.2U L=0.4U AS=0.72P PS=1.2U AD=1.18P PD=2.00667U
M59           44     CLK     GND     GND       NMOS W=4.8U L=0.4U AS=2.88P PS=1.2U AD=4.72P PD=8.02667U
M60            5      23      24     GND       NMOS W=1.2U L=0.4U AS=0.72P PS=1.2U AD=0.72P PD=1.2U
M61            5      13      C1     GND       NMOS W=1.2U L=0.4U AS=0.72P PS=1.2U AD=1.32P PD=3.4U
M62           26       3     GND     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=2.36P PD=4.01333U
M63           48       5      58     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.44P PD=1.2U
M64            7       3      47     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.56P PD=1.3U
M65          GND       4      58     GND       NMOS W=2.4U L=0.4U AS=2.36P PS=4.01333U AD=1.44P PD=1.2U
M66           47      14     GND     GND       NMOS W=2.4U L=0.4U AS=1.56P PS=1.3U AD=2.36P PD=4.01333U
M67           27      48     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M68           13       7     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M69            6      27     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M70           14      29      49     GND       NMOS W=4.8U L=0.4U AS=5.28P PS=7U AD=2.88P PD=1.2U
M71           16       6     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M72           49       3     GND     GND       NMOS W=4.8U L=0.4U AS=2.88P PS=1.2U AD=4.72P PD=8.02667U
M73           28       8     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M74           29       7     GND     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=2.36P PD=4.01333U
M75           30      28     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M76            8       7      51     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.56P PD=1.3U
M77           31      30     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M78           51      15     GND     GND       NMOS W=2.4U L=0.4U AS=1.56P PS=1.3U AD=2.36P PD=4.01333U
M79           32      31     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M80            9       8     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M81           33      32     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M82           34      33     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M83           15      37      52     GND       NMOS W=4.8U L=0.4U AS=5.28P PS=7U AD=2.88P PD=1.2U
M84           52       7     GND     GND       NMOS W=4.8U L=0.4U AS=2.88P PS=1.2U AD=4.72P PD=8.02667U
M85           35      34     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M86        O_CLK      35     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M87           37       8     GND     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=2.36P PD=4.01333U
M88           38      C2     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M89           39      16      54     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.56P PD=1.3U
M90           54      18     GND     GND       NMOS W=2.4U L=0.4U AS=1.56P PS=1.3U AD=2.36P PD=4.01333U
M91          GND      38      59     GND       NMOS W=2.4U L=0.4U AS=2.36P PS=4.01333U AD=1.44P PD=1.2U
M92           19       8      59     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.44P PD=1.2U
M93        D_CLK      39     GND     GND       NMOS W=1.2U L=0.4U AS=1.32P PS=3.4U AD=1.18P PD=2.00667U
M94          GND      C2      60     GND       NMOS W=2.4U L=0.4U AS=2.36P PS=4.01333U AD=1.44P PD=1.2U
M95           18      42      55     GND       NMOS W=4.8U L=0.4U AS=5.28P PS=7U AD=2.88P PD=1.2U
M96           20       9      60     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.44P PD=1.2U
M97           55      16     GND     GND       NMOS W=4.8U L=0.4U AS=2.88P PS=1.2U AD=4.72P PD=8.02667U
M98           41      19      61     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=1.44P PD=1.2U
M99           42      41     GND     GND       NMOS W=2.4U L=0.4U AS=2.64P PS=4.6U AD=2.36P PD=4.01333U
M100         GND      20      61     GND       NMOS W=2.4U L=0.4U AS=2.36P PS=4.01333U AD=1.44P PD=1.2U
*---------------------------------------------------
*	# OF MOSEF NMOS       : 52
*---------------------------------------------------
*
