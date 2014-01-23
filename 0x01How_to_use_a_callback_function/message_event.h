/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#ifndef MESSAGE_EVENT_H
#define MESSAGE_EVENT_H

#include <ncurses.h>

#define NO_INPUT_DATA	(-1)
#define NO_KEY_DATA		(-1)
#define NO_OTHER_DATA	(-1)

/*redefine mouse event according to mouse event of The Ncurses  library*/
#define MOUSE_LEFT_DOWN 			BUTTON1_PRESSED
#define MOUSE_LEFT_UP				BUTTON1_RELEASED
#define MOUSE_LEFT_CLICK 			BUTTON1_CLICKED
#define MOUSE_LEFT_DOUBLE_CLICK		BUTTON1_DOUBLE_CLICKED
#define MOUSE_LEFT_TRIPLE_CLICK		BUTTON1_TRIPLE_CLICKED


#define MOUSE_WHEEL_DOWN 			BUTTON2_PRESSED
#define MOUSE_WHEEL_UP				BUTTON2_RELEASED
#define MOUSE_WHEEL_CLICK			BUTTON2_CLICKED//0x100		//get the value by myself via testing mouse
#define MOUSE_WHEEL_DOUBLE_CLICK	BUTTON2_DOUBLE_CLICKED
#define MOUSE_WHEEL_TRIPLE_CLICK	BUTTON2_TRIPLE_CLICKED

#define MOUSE_WHEEL_OUT		0x80000		
#define MOUSE_WHEEL_IN		0x8000000

#define MOUSE_RIGHT_DOWN 			BUTTON3_PRESSED			//unused
#define MOUSE_RIGHT_UP				BUTTON3_RELEASED		//unused
#define MOUSE_RIGHT_CLICK 			BUTTON3_CLICKED			//unused
#define MOUSE_RIGHT_DOUBLE_CLICK	BUTTON3_DOUBLE_CLICKED	//unused
#define MOUSE_RIGHT_TRIPLE_CLICK	BUTTON3_TRIPLE_CLICKED	//unused


typedef int 	m_evt_no_input_t;
typedef MEVENT 	m_evt_mouse_t;
typedef int	   	m_evt_key_t;
typedef int 	m_evt_other_t;

typedef enum message_event_type{
	M_EVT_NO_INPUT=-1,
	M_EVT_MOUSE=0,
	M_EVT_KEY,
	M_EVT_OTHER,
}m_evt_type_t;

typedef union message_event_param{
	struct{
		m_evt_no_input_t no_input;
	}no_input_t;
	
	struct{
		m_evt_mouse_t mouse;
	}mouse_t;

	struct{
		m_evt_key_t key;
	}key_t;

	struct{
		m_evt_other_t other;
	}other_t;
}m_evt_param_t;

typedef struct message_event_code{
	m_evt_type_t	m_evt_type;
	m_evt_param_t	m_evt_param;
}m_evt_code_t;	//T_M_EVENT_CODE;

#endif	/*MESSAGE_EVENT_H*/
