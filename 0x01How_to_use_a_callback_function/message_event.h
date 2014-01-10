/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#ifndef MESSAGE_EVENT_H
#define MESSAGE_EVENT_H

#include <ncurses.h>

#define NO_INPUT_DATA	(-1)
#define NO_KEY_DATA		(-1)
#define NO_OTHER_DATA	(-1)

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
