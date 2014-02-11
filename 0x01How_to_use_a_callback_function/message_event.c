/**
  *  Copyright (C) 2013-12-21  Handsome Zhou
  */

#include "message_event.h"

m_evt_type_t get_m_evt_type(const m_evt_code_t *m_evt_code)
{
	const m_evt_code_t *mec=m_evt_code;
	if(NULL==mec){
		return M_EVT_NO_INPUT;
	}

	return mec->m_evt_type;
}

m_evt_key_t get_m_evt_key(const m_evt_code_t *m_evt_code)
{
	const m_evt_code_t *mec=m_evt_code;
	if(NULL==mec){
		return NO_KEY_DATA;
	}

	return mec->m_evt_param.key_t.key;
}
	
m_evt_mouse_t *get_m_evt_mouse(m_evt_code_t *m_evt_code)
{
	m_evt_code_t *mec=m_evt_code;
	if(NULL==mec){
		return NULL;
	}

	return &mec->m_evt_param.mouse_t.mouse;
}


