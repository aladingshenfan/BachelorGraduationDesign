
################################################################
# This is a generated script based on design: design_1
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2014.2
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   puts "ERROR: This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_1_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#    create_project project_1 myproj -part xc7a35tcpg236-1


# CHANGE DESIGN NAME HERE
set design_name design_1

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# CHECKING IF PROJECT EXISTS
if { [get_projects -quiet] eq "" } {
   puts "ERROR: Please open or create a project!"
   return 1
}


# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} ne "" && ${cur_design} eq ${design_name} } {

   # Checks if design is empty or not
   if { $list_cells ne "" } {
      set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
      set nRet 1
   } else {
      puts "INFO: Constructing design in IPI design <$design_name>..."
   }
} elseif { ${cur_design} ne "" && ${cur_design} ne ${design_name} } {

   if { $list_cells eq "" } {
      puts "INFO: You have an empty design <${cur_design}>. Will go ahead and create design..."
   } else {
      set errMsg "ERROR: Design <${cur_design}> is not empty! Please do not source this script on non-empty designs."
      set nRet 1
   }
} else {

   if { [get_files -quiet ${design_name}.bd] eq "" } {
      puts "INFO: Currently there is no design <$design_name> in project, so creating one..."

      create_bd_design $design_name

      puts "INFO: Making design <$design_name> as current_bd_design."
      current_bd_design $design_name

   } else {
      set errMsg "ERROR: Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
      set nRet 3
   }

}

puts "INFO: Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   puts $errMsg
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports

  # Create ports
  set A_VAUXN [ create_bd_port -dir I A_VAUXN ]
  set A_VAUXP [ create_bd_port -dir I A_VAUXP ]
  set B_VAUXN [ create_bd_port -dir I B_VAUXN ]
  set B_VAUXP [ create_bd_port -dir I B_VAUXP ]
  set Config_Done [ create_bd_port -dir O Config_Done ]
  set Move_EN [ create_bd_port -dir I Move_EN ]
  set OV7725_D [ create_bd_port -dir I -from 7 -to 0 OV7725_D ]
  set OV7725_HREF [ create_bd_port -dir I OV7725_HREF ]
  set OV7725_PCLK [ create_bd_port -dir I OV7725_PCLK ]
  set OV7725_SIOC [ create_bd_port -dir O OV7725_SIOC ]
  set OV7725_SIOD [ create_bd_port -dir IO OV7725_SIOD ]
  set OV7725_VSYNC [ create_bd_port -dir I OV7725_VSYNC ]
  set OV7725_XCLK [ create_bd_port -dir O -type clk OV7725_XCLK ]
  set btn_ColorExtract [ create_bd_port -dir I btn_ColorExtract ]
  set clk100 [ create_bd_port -dir I -type clk clk100 ]
  set pwm_out_x [ create_bd_port -dir O pwm_out_x ]
  set pwm_out_y [ create_bd_port -dir O pwm_out_y ]
  set rst [ create_bd_port -dir I rst ]
  set sw_ColorClear [ create_bd_port -dir I sw_ColorClear ]
  set vga_blue [ create_bd_port -dir O -from 3 -to 0 vga_blue ]
  set vga_green [ create_bd_port -dir O -from 3 -to 0 vga_green ]
  set vga_hsync [ create_bd_port -dir O vga_hsync ]
  set vga_red [ create_bd_port -dir O -from 3 -to 0 vga_red ]
  set vga_vsync [ create_bd_port -dir O vga_vsync ]

  # Create instance: I2C_AV_Config_0, and set properties
  set I2C_AV_Config_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:I2C_AV_Config:1.0 I2C_AV_Config_0 ]

  # Create instance: Motor_Ctrl_0, and set properties
  set Motor_Ctrl_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:Motor_Ctrl:1.0 Motor_Ctrl_0 ]

  # Create instance: bram_0, and set properties
  set bram_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:bram:1.0 bram_0 ]

  # Create instance: clk_wiz_0, and set properties
  set clk_wiz_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:5.1 clk_wiz_0 ]
  set_property -dict [ list CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {50.000} CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {25.000} CONFIG.CLKOUT2_USED {true} CONFIG.CLKOUT3_USED {false} CONFIG.USE_LOCKED {false} CONFIG.USE_RESET {false}  ] $clk_wiz_0

  # Create instance: colorDetect_0, and set properties
  set colorDetect_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:colorDetect:1.0 colorDetect_0 ]

  # Create instance: debounce_0, and set properties
  set debounce_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:debounce:1.0 debounce_0 ]

  # Create instance: dilate_0, and set properties
  set dilate_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:dilate:1.0 dilate_0 ]

  # Create instance: erode_0, and set properties
  set erode_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:erode:1.0 erode_0 ]

  # Create instance: ov7725_capture_0, and set properties
  set ov7725_capture_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:ov7725_capture:1.0 ov7725_capture_0 ]

  # Create instance: rgb2hsv_top_0, and set properties
  set rgb2hsv_top_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:rgb2hsv_top:1.0 rgb2hsv_top_0 ]

  # Create instance: rgb565_rgb888_0, and set properties
  set rgb565_rgb888_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:rgb565_rgb888:1.0 rgb565_rgb888_0 ]

  # Create instance: rgb888_rgb565_0, and set properties
  set rgb888_rgb565_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:rgb888_rgb565:1.0 rgb888_rgb565_0 ]

  # Create instance: vga_0, and set properties
  set vga_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:vga:1.0 vga_0 ]

  # Create port connections
  connect_bd_net -net A_VAUXN_1 [get_bd_ports A_VAUXN] [get_bd_pins Motor_Ctrl_0/A_VAUXN]
  connect_bd_net -net A_VAUXP_1 [get_bd_ports A_VAUXP] [get_bd_pins Motor_Ctrl_0/A_VAUXP]
  connect_bd_net -net B_VAUXN_1 [get_bd_ports B_VAUXN] [get_bd_pins Motor_Ctrl_0/B_VAUXN]
  connect_bd_net -net B_VAUXP_1 [get_bd_ports B_VAUXP] [get_bd_pins Motor_Ctrl_0/B_VAUXP]
  connect_bd_net -net I2C_AV_Config_0_Config_Done [get_bd_ports Config_Done] [get_bd_pins I2C_AV_Config_0/Config_Done]
  connect_bd_net -net I2C_AV_Config_0_I2C_SCLK [get_bd_ports OV7725_SIOC] [get_bd_pins I2C_AV_Config_0/I2C_SCLK]
  connect_bd_net -net Motor_Ctrl_0_pwm_x [get_bd_ports pwm_out_x] [get_bd_pins Motor_Ctrl_0/pwm_x]
  connect_bd_net -net Motor_Ctrl_0_pwm_y [get_bd_ports pwm_out_y] [get_bd_pins Motor_Ctrl_0/pwm_y]
  connect_bd_net -net Move_EN_1 [get_bd_ports Move_EN] [get_bd_pins Motor_Ctrl_0/Move_EN]
  connect_bd_net -net Net [get_bd_ports OV7725_SIOD] [get_bd_pins I2C_AV_Config_0/I2C_SDAT]
  connect_bd_net -net bram_0_doutb [get_bd_pins bram_0/doutb] [get_bd_pins rgb565_rgb888_0/rgb565]
  connect_bd_net -net btn_ColorExtract_1 [get_bd_ports btn_ColorExtract] [get_bd_pins colorDetect_0/btn_ColorExtract]
  connect_bd_net -net clk_in1_1 [get_bd_ports clk100] [get_bd_pins clk_wiz_0/clk_in1]
  connect_bd_net -net clk_wiz_0_clk_out1 [get_bd_pins Motor_Ctrl_0/clk_50M] [get_bd_pins clk_wiz_0/clk_out1] [get_bd_pins debounce_0/clk]
  connect_bd_net -net clk_wiz_0_clk_out2 [get_bd_ports OV7725_XCLK] [get_bd_pins I2C_AV_Config_0/iCLK] [get_bd_pins bram_0/clkb] [get_bd_pins clk_wiz_0/clk_out2] [get_bd_pins colorDetect_0/PClk] [get_bd_pins dilate_0/PCLK] [get_bd_pins erode_0/PCLK] [get_bd_pins rgb2hsv_top_0/pclk] [get_bd_pins vga_0/clk25]
  connect_bd_net -net colorDetect_0_Binary_PreProcess [get_bd_pins colorDetect_0/Binary_PreProcess] [get_bd_pins erode_0/pix_i]
  connect_bd_net -net colorDetect_0_RGB24_dis [get_bd_pins colorDetect_0/RGB24_dis] [get_bd_pins rgb888_rgb565_0/rgb888]
  connect_bd_net -net colorDetect_0_center_h [get_bd_pins Motor_Ctrl_0/x] [get_bd_pins colorDetect_0/center_h]
  connect_bd_net -net colorDetect_0_center_v [get_bd_pins Motor_Ctrl_0/y] [get_bd_pins colorDetect_0/center_v]
  connect_bd_net -net d_1 [get_bd_ports OV7725_D] [get_bd_pins ov7725_capture_0/d]
  connect_bd_net -net debounce_0_o [get_bd_pins I2C_AV_Config_0/rst] [get_bd_pins debounce_0/o]
  connect_bd_net -net dilate_0_pix_o [get_bd_pins colorDetect_0/Binary_PostProcess] [get_bd_pins dilate_0/pix_o]
  connect_bd_net -net erode_0_pix_o [get_bd_pins dilate_0/pix_i] [get_bd_pins erode_0/pix_o]
  connect_bd_net -net href_1 [get_bd_ports OV7725_HREF] [get_bd_pins ov7725_capture_0/href]
  connect_bd_net -net ov7725_capture_0_addr [get_bd_pins bram_0/addra] [get_bd_pins ov7725_capture_0/addr]
  connect_bd_net -net ov7725_capture_0_dout [get_bd_pins bram_0/dina] [get_bd_pins ov7725_capture_0/dout]
  connect_bd_net -net ov7725_capture_0_we [get_bd_pins bram_0/wea] [get_bd_pins ov7725_capture_0/we]
  connect_bd_net -net pclk_1 [get_bd_ports OV7725_PCLK] [get_bd_pins bram_0/clka] [get_bd_pins ov7725_capture_0/pclk]
  connect_bd_net -net rgb2hsv_top_0_HSV24 [get_bd_pins colorDetect_0/HSV24] [get_bd_pins rgb2hsv_top_0/HSV24]
  connect_bd_net -net rgb565_rgb888_0_rgb888 [get_bd_pins colorDetect_0/RGB24] [get_bd_pins rgb2hsv_top_0/RGB24] [get_bd_pins rgb565_rgb888_0/rgb888]
  connect_bd_net -net rgb888_rgb565_0_rgb565 [get_bd_pins rgb888_rgb565_0/rgb565] [get_bd_pins vga_0/frame_pixel]
  connect_bd_net -net rst_1 [get_bd_ports rst] [get_bd_pins Motor_Ctrl_0/reset] [get_bd_pins debounce_0/i]
  connect_bd_net -net sw_ColorClear_1 [get_bd_ports sw_ColorClear] [get_bd_pins colorDetect_0/sw_ColorClear]
  connect_bd_net -net vga_0_Hcnt_signal [get_bd_pins colorDetect_0/VtcHCnt] [get_bd_pins dilate_0/VtcHCnt] [get_bd_pins erode_0/VtcHCnt] [get_bd_pins vga_0/Hcnt_signal]
  connect_bd_net -net vga_0_Vcnt_signal [get_bd_pins colorDetect_0/VtcVCnt] [get_bd_pins dilate_0/VtcVCnt] [get_bd_pins erode_0/VtcVCnt] [get_bd_pins vga_0/Vcnt_signal]
  connect_bd_net -net vga_0_frame_addr [get_bd_pins bram_0/addrb] [get_bd_pins vga_0/frame_addr]
  connect_bd_net -net vga_0_vga_blue [get_bd_ports vga_blue] [get_bd_pins vga_0/vga_blue]
  connect_bd_net -net vga_0_vga_green [get_bd_ports vga_green] [get_bd_pins vga_0/vga_green]
  connect_bd_net -net vga_0_vga_hsync [get_bd_ports vga_hsync] [get_bd_pins vga_0/vga_hsync]
  connect_bd_net -net vga_0_vga_red [get_bd_ports vga_red] [get_bd_pins vga_0/vga_red]
  connect_bd_net -net vga_0_vga_vsync [get_bd_ports vga_vsync] [get_bd_pins vga_0/vga_vsync]
  connect_bd_net -net vsync_1 [get_bd_ports OV7725_VSYNC] [get_bd_pins Motor_Ctrl_0/vsync_in] [get_bd_pins ov7725_capture_0/vsync]

  # Create address segments
  

  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


