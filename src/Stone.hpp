#ifndef SERIAL_STONE_HMI
#define SERIAL_STONE_HMI

#define STONE_sys_state 0x0000        //System states
#define STONE_sys_hello 0x0001        //System return code for communication test command (sys_hello)
#define STONE_sys_version 0x0002      //System firmware information return for get_version command
#define STONE_control_write_hex 0x0021                 //The response to the write_hex instruction
#define STONE_control_write_line 0x0023                //The response to the write_line instruction
#define STONE_control_write_text 0x0025                //The response to the write_text instruction
#define STONE_control_read_hex 0x0020 //The response to the read_hex instruction
#define STONE_control_read_line 0x0022                 //The response to the read_line instruction
#define STONE_control_get_file_size 0x0024             //The response to the get_file_size instruction
#define STONE_control_delete_file 0x0026               //The response to the delete_file instruction
#define STONE_control_set_rename 0x0027                //The response to the set_rename instruction
#define STONE_control_download_file 0x0028             //The response to the download_file instruction
#define STONE_control_unmount_disk 0x002A              //The response to the unmount_disk instruction
#define STONE_control_get_xy 0x0400   //The response to the get_xy instruction
#define STONE_control_get_wh 0x0401   //The response to the get_wh instruction
#define STONE_control_get_min 0x1160  //The response to the get_min instruction
#define STONE_control_get_max 0x1161  //The response to the get_max instruction
#define STONE_control_button 0x1001   //button status send
#define STONE_control_button_u 0x1002 //button key value send (will be released soon)
#define STONE_control_switch 0x1010   //switch value changed return
#define STONE_control_check_button 0x1020              //check button value changed return
#define STONE_control_radio_button 0x1030              //radio button value changed return initiative
#define STONE_control_radio_button_s 0x1031            //radio button value changed return passively(by get_checked command from MCU)
#define STONE_control_slider 0x1040   //slider value changing return
#define STONE_control_slider_over 0x1041               //slider value changed return
#define STONE_control_progress_bar 0x1050              //progress bar value changed return
#define STONE_control_progress_bar_p 0x1051            //progress bar percentage return passively, by get_percent command from MCU
#define STONE_control_label_text 0x1060                //label text content return passively (The display will only return the command after received the get_text command from MCU)
#define STONE_control_label_value 0x1062               //label value return (float type)(while the label was targeted by the set_value function on the button, the code will return once the value is changed)
#define STONE_control_edit_text 0x1070                 //edit text return (Initiatively or passively. It can be returned after the edit text changed, or returned by get_text command)
#define STONE_control_edit_int 0x1071 //edit data return(int type)
#define STONE_control_edit_float 0x1072                //edit data return(float type)
#define STONE_control_text_selector_text 0x1080        //text selector text content return passively (by get_text command)
#define STONE_control_text_selector_value 0x1081       //text selector value return initiatively (int type value, can be read by get_value command from MCU)
#define STONE_control_text_selector_num 0x1082         //text selector index number return passively (int type value by get_value command from MCU)
#define STONE_control_image 0x1090    //Image key Delivers the system key
#define STONE_control_image_u 0x1091  //Image key Delivers a user-defined key value
#define STONE_control_image_value 0x1092               //image_value value return (float type, can be returned initiatively or passively)
#define STONE_control_spin_box_text 0x10A0             //Spin_box text delivery
#define STONE_control_spin_box_int 0x10A1              //Spin_box value delivered (int type)
#define STONE_control_spin_box_float 0x10A2            //Spin_box value delivered (float type)
#define STONE_control_combo_box_text 0x10B0            //combo_box text delivery
#define STONE_control_combo_box_int 0x10B1             //combo_box value delivered (int type)
#define STONE_control_combo_box_float 0x10B2           //combo_box value delivered (float type)
#define STONE_control_combo_box_num 0x10B8             //combo_box serial number is delivered
#define STONE_control_mledit_text 0x10C0               //mledit text delivery
#define STONE_control_chart_view_value 0x10D1          //chart_view value delivered
#define STONE_control_chart_view_capacity 0x10D2       //chart_view capacity delivery (response to the instruction get_capacity)
#define STONE_control_progress_circle_value 0x10E0     //progress_circle value delivered (float type)
#define STONE_control_progress_circle_p 0x10E1         //progress_circle percentage return passively, by get_percent command from MCU
#define STONE_control_digit_clock 0x10F0               //digit_clock Date + time return (get_date in MCU)
#define STONE_control_hscroll_label 0x1100             //hscroll_label Text return (the GEt_TEXT instruction is used in the MCU)
#define STONE_control_slide_indicator_value 0x1110     //gets the current value of the indicator (option)
#define STONE_control_slide_view 0x1120                //gets the sequence number of the slide_view
#define STONE_control_slide_menu 0x1130                //gets the sequence number of the slide_menu
#define STONE_control_tab_button 0x1140                //gets the tab_button value
#define STONE_control_tab_view 0x1150 //gets the serial number of the tab_view

class Stone {
	public:
		struct Receive {
			unsigned int        cmd;
			unsigned int        len;
			#if MCU_ARDUINO || MCU_ESP    //Arduino int 2bit
			long                value;
			float               floatValue;
			unsigned long long  longValue;
			#else
			int                 value;
			float               floatValue;
			unsigned long       longValue;
			#endif
			unsigned char       *data;
			unsigned char       *widget;
			unsigned char       *text;
		};

		/**
		 * @return bool flag true because there was a receive.
		 */
		static bool parse(Receive &receive, const unsigned char * buffer, size_t length);

		static uint16_t crc(const unsigned char *buffer, unsigned int length);

	private:
		static void parseCmd(Receive &receive, const unsigned char *buffer, size_t length);

		static inline void initData(unsigned char * data, size_t length) {
			data = new unsigned char[length + 1];
		}
};

#endif
