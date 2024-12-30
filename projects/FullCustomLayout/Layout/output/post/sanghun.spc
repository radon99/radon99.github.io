SANGHUN
*******************************************************************************
**            MyChip Station LayNet Pro 2017 
**            Copyright(c) 1992-2017 MyCAD, Inc. 
**            TIME = 15:49:53  DATE = 05/31/23 
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
C1             2      11 0.00015088P 
C2            11      C0 0.00015088P 
C3             2      C0 0.00015088P 
C4           CLK      12 0.00015088P 
C5            11       2 0.00015088P 
C6            C0       2 0.00036144P 
C7            23      13 0.00015088P 
C8            13      C1 0.00015088P 
C9            23      C1 0.00015088P 
C10           26     CLK 0.00015088P 
C11           26       3 0.00015088P 
C12          CLK       3 0.00015088P 
C13           C1      23 0.00034828P 
C14           13      23 0.00016316P 
C15           48       5 0.00015088P 
C16           48       4 0.00015088P 
C17            3      14 0.00015088P 
C18            6      27 0.00015088P 
C19           29       3 0.00015088P 
C20           29       7 0.00015088P 
C21            3       7 0.00015088P 
C22           28       8 0.00015088P 
C23           31      30 0.00015088P 
C24            7      15 0.00015088P 
C25           33      32 0.00015088P 
C26           37       7 0.00015088P 
C27           35      34 0.00015088P 
C28           37       8 0.00015088P 
C29            7       8 0.00015088P 
C30           16      18 0.00015088P 
C31           19       8 0.00015088P 
C32           20       9 0.00015088P 
C33           42      16 0.00015088P 
C34           42      41 0.00015088P 
C35           16      41 0.00015088P 
C36           41      19 0.00015088P 
*---------------------------------------------------
*	# OF CAPACITOR C          : 36
*---------------------------------------------------
*
C37            3     CLK 0.0001643P 
C38            3      12 9.6e-005P 
C39           23      13 0.0001124P 
C40           C0      11 0.0002084P 
C41           21      C0 9.42e-005P 
C42            5      13 8.51e-005P 
C43            4       2 0.0001811P 
C44            4      11 8.51e-005P 
C45           24      13 8.51e-005P 
C46           24      23 8.51e-005P 
C47           C1      13 0.0001993P 
C48           15      37 8.51e-005P 
C49           26     CLK 8.51e-005P 
C50           29       3 8.51e-005P 
C51            5      23 0.0001811P 
C52            7      14 9.6e-005P 
C53            7       3 0.0001643P 
C54           39      16 8.51e-005P 
C55           37       7 8.51e-005P 
C56           39      18 9.6e-005P 
C57          VDD      18 0.0001124P 
C58            8       7 0.0001643P 
C59            8      15 9.6e-005P 
C60           18      42 8.51e-005P 
C61           42      16 8.51e-005P 
C62           12      26 8.51e-005P 
C63          VDD      14 0.0001124P 
C64          VDD      15 0.0001124P 
C65           21       2 8.51e-005P 
C66           14      29 8.51e-005P 
C67           21      11 8.51e-005P 
*---------------------------------------------------
*	# OF CAPACITOR C          : 31
*---------------------------------------------------
*
C68           11      21 0.00019456P 
C69           C0      21 0.00019456P 
C70            2      21 0.00019456P 
C71           11       4 0.00019456P 
C72           C0       4 0.00019456P 
C73          CLK       3 0.00080296P 
C74           11      C0 0.00019456P 
C75          CLK      11 0.00064456P 
C76           13      23 0.00012696P 
C77          CLK      12 0.00019456P 
C78           13      24 0.00019456P 
C79           C1      24 0.00019456P 
C80           23      24 0.00019456P 
C81           13       5 0.00019456P 
C82           C1       5 0.00019456P 
C83           13      C1 0.00019456P 
C84            3      26 0.00019456P 
C85            7     VDD 0.0002216P 
C86            3       7 0.00091112P 
C87            3      13 0.00064456P 
C88            3      14 0.00019456P 
C89            7      29 0.00019456P 
C90            8     VDD 0.0002216P 
C91           30      31 0.00019456P 
C92            7       8 0.00091112P 
C93           32      33 0.00019456P 
C94            7       9 0.00064456P 
C95            7      15 0.00019456P 
C96           34      35 0.00019456P 
C97           39     VDD 0.0002216P 
C98          VDD      39 0.00019456P 
C99           19       8 0.00035272P 
C100          16      39 0.00019456P 
C101          16   D_CLK 0.00064456P 
C102          16      18 0.00019456P 
C103          20       9 0.00035272P 
C104         GND      41 0.00060544P 
*---------------------------------------------------
*	# OF CAPACITOR C          : 37
*---------------------------------------------------
*

VT_I4 CLK GND PULSE ( 0 5 0N 0.11N 0.11N 0.44N 1.1N )
CT_I6 O_CLK GND 500F
CT_I8 D_CLK GND 500F
VT_I2 C2 GND PWL ( 0 0 )
VT_I3 C1 GND PWL ( 0 0 )
VT_I10 C0 GND PWL ( 0 0 )
VDD VDD 0 PULSE ( 0 5 0N 1N 1N 1 2 )
VSS GND 0 DC 0
.TRAN 1n 40n

* TSMC 0352P4M
* SPICE BSIM3 VERSION 3.1 PARAMETERS
* SPICE 3f5 Level 8, Star-HSPICE Level 49, UTMOST Level 8
.MODEL NMOS NMOS (                                 LEVEL   = 49
+VERSION = 3.1            TNOM    = 27             TOX     = 7.6E-9
+XJ      = 1E-7           NCH     = 2.3579E17      VTH0    = 0.5027514
+K1      = 0.5359893      K2      = 0.0258172      K3      = 24.6606744
+K3B     = 1.4055348      W0      = 5.355464E-6    NLX     = 2.404522E-9
+DVT0W   = 0              DVT1W   = 0              DVT2W   = 0
+DVT0    = -0.120252      DVT1    = 3.084588E-3    DVT2    = 0.470688
+U0      = 417.429294     UA      = -1.40534E-13   UB      = 1.355832E-18
+UC      = 2.939828E-11   VSAT    = 1.208882E5     A0      = 0.9319916
+AGS     = 0.1686015      B0      = 1.288356E-6    B1      = 5E-6
+KETA    = 0.0105706      A1      = 0              A2      = 1
+RDSW    = 1.103044E3     PRWG    = 1.750872E-3    PRWB    = -0.0916512
+WR      = 1              WINT    = 6.910593E-8    LINT    = 1.993462E-8
+XL      = -2E-8          XW      = 0              DWG     = 1.047524E-9
+DWB     = 1.084571E-8    VOFF    = -0.0906265     NFACTOR = 0.6164962
+CIT     = 0              CDSC    = 5.145568E-6    CDSCD   = 0
+CDSCB   = 0              ETA0    = 4.63499E-3     ETAB    = -9.189583E-4
+DSUB    = 0.1150044      PCLM    = 0.7703416      PDIBLC1 = 0.3438859
+PDIBLC2 = 8.526878E-3    PDIBLCB = 0.0845601      DROUT   = 0.6859339
+PSCBE1  = 7.23225E9      PSCBE2  = 5.005586E-10   PVAG    = 0.4108257
+DELTA   = 0.01           MOBMOD  = 1              PRT     = 0
+UTE     = -1.5           KT1     = -0.11          KT1L    = 0
+KT2     = 0.022          UA1     = 4.31E-9        UB1     = -7.61E-18
+UC1     = -5.6E-11       AT      = 3.3E4          WL      = 0
+WLN     = 1              WW      = -1.22182E-15   WWN     = 1.1837
+WWL     = 0              LL      = 0              LLN     = 1
+LW      = 0              LWN     = 1              LWL     = 0
+CAPMOD  = 2              XPART   = 0.4            CGDO    = 2.95E-10
+CGSO    = 2.95E-10       CGBO    = 1E-11          CJ      = 1.08158E-3
+PB      = 0.7719669      MJ      = 0.3252096      CJSW    = 3.480034E-10
+PBSW    = 0.99           MJSW    = 0.1576976      PVTH0   = -0.0122678
+PRDSW   = -93.3365259    PK2     = -3.470912E-3   WKETA   = -3.503848E-3
+LKETA   = -0.0105386      )
*
.MODEL PMOS PMOS (                                 LEVEL   = 49
+VERSION = 3.1            TNOM    = 27             TOX     = 7.6E-9
+XJ      = 1E-7           NCH     = 8.52E16        VTH0    = -0.6821549
+K1      = 0.4197546      K2      = -6.11453E-3    K3      = 35.791795
+K3B     = -2.796173      W0      = 1.990794E-6    NLX     = 4.309814E-7
+DVT0W   = 0              DVT1W   = 0              DVT2W   = 0
+DVT0    = 1.134781       DVT1    = 0.3272645      DVT2    = -1.051562E-3
+U0      = 141.3184274    UA      = 1.024889E-10   UB      = 1.354611E-18
+UC      = -3.30244E-11   VSAT    = 1.6171E5       A0      = 0.6693235
+AGS     = 0.2959248      B0      = 2.86196E-6     B1      = 5E-6
+KETA    = -6.382387E-3   A1      = 0              A2      = 1
+RDSW    = 3.44286E3      PRWG    = -0.0626736     PRWB    = 0.0981315
+WR      = 1              WINT    = 5.340142E-8    LINT    = 1.410986E-9
+XL      = -2E-8          XW      = 0              DWG     = -4.209302E-9
+DWB     = 1.12145E-8     VOFF    = -0.1154702     NFACTOR = 2
+CIT     = 0              CDSC    = 0              CDSCD   = 0
+CDSCB   = 4.724734E-5    ETA0    = 0.0115959      ETAB    = 2.08259E-4
+DSUB    = 0.2766226      PCLM    = 7.8965744      PDIBLC1 = 1.97648E-3
+PDIBLC2 = 8.825766E-3    PDIBLCB = 2.37472E-3     DROUT   = 0.4321935
+PSCBE1  = 3.010835E10    PSCBE2  = 7.998967E-10   PVAG    = 15
+DELTA   = 0.01           MOBMOD  = 1              PRT     = 0
+UTE     = -1.5           KT1     = -0.11          KT1L    = 0
+KT2     = 0.022          UA1     = 4.31E-9        UB1     = -7.61E-18
+UC1     = -5.6E-11       AT      = 3.3E4          WL      = 0
+WLN     = 1              WW      = -5.22182E-16   WWN     = 1.195
+WWL     = 0              LL      = 0              LLN     = 1
+LW      = 0              LWN     = 1              LWL     = 0
+CAPMOD  = 2              XPART   = 0.4            CGDO    = 2.77E-10
+CGSO    = 2.77E-10       CGBO    = 1E-11          CJ      = 1.417679E-3
+PB      = 0.99           MJ      = 0.5636812      CJSW    = 4.292884E-10
+PBSW    = 0.99           MJSW    = 0.3497357      PVTH0   = 0.0116448
+PRDSW   = -58.3059685    PK2     = 1.654991E-3    WKETA   = -6.310553E-4
+LKETA   = 1.189744E-3     )
*
