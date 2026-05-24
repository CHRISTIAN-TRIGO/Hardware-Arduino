/* 
 ********  ING.LUIS ENRIQUE DE LA TORRE VERA  ***************************
 *****CENTRO DE SISTEMASS DE COMPUTO Y ELECTRONICA ********************
 */

#include "a_rebote.h"

a_rebote::a_rebote(uint8_t pin, uint8_t mode)
{
	// Configure io pin for this button
	switch (mode) {
	case E_A_REBOTE_PULLUP:
	case E_A_REBOTE_PULLDOWN:
		pinMode(pin, INPUT);
	case E_A_REBOTE_PULLUP_INTERNAL:
		pinMode(pin, INPUT_PULLUP);
	}
	// button FSM and timers initial state
	_state = E_BTN_WAIT_PRESS;
	_debounceTimer = 0;
	_clicksTimer = 0;

	// pre-set configuration fields
	_pin = pin;
	_mode = mode;
	_holdTimeSetting = 5000;
	_debounceTimeSetting = 20;

	// pre-set external read-only fields
	_pressCount = 0;
	_holdTime = 0;
	_clicks = 0;

	// Clear callback pointers
	cb_onPress = 0;
	cb_onHold = 0;
	cb_onRelease = 0;
	cb_onClick = 0;

	// estado de las banderas
	_flags = 0;
}

void a_rebote::setHoldTime(uint16_t time)
{
	_holdTimeSetting = time;
}

void a_rebote::setDebounceTime(uint16_t time)
{
	_debounceTimeSetting = time;
}

void a_rebote::setPressHandler(a_reboteEventHandler_t handler)
{
	cb_onPress = handler;
}

void a_rebote::setHoldHandler(a_reboteEventHandler_t handler)
{
	cb_onHold = handler;
}

void a_rebote::setReleaseHandler(a_reboteEventHandler_t handler)
{
	cb_onRelease = handler;
}

void a_rebote::setClicksHandler(a_reboteEventHandler_t handler)
{
	cb_onClick = handler;
}

uint8_t a_rebote::getPin()
{
	return _pin;
}

uint16_t a_rebote::getPressCount()
{
	return _pressCount;
}

uint16_t a_rebote::getHoldTime()
{
	return _holdTime;
}

uint16_t a_rebote::getClicks()
{
	return _clicks;
}

bool a_rebote::Consecutivo()
{
	process();
	// If FSM reached the E_BNT_WAIT_RELEASE state
	// we have the button pressed and return ture, otherwise return false
	return(_state == E_BTN_WAIT_RELEASE) ? true : false;
}

bool a_rebote::al_presionar()
{
	process();
	if (_flags & A_REBOTE_FLAG_al_presionar) {
		// Clear the flag
		_flags = _flags & ~A_REBOTE_FLAG_al_presionar;
		return true;
	}
	return false;
}

bool a_rebote::wasLongPress()
{
	process();
	if (_flags & A_REBOTE_FLAG_LONGPRESS) {
		// limpia las banderas
		_flags = _flags & ~A_REBOTE_FLAG_LONGPRESS;
		return true;
	}
	return false;
}

bool a_rebote::isFirstHold()
{
	return(_flags & A_REBOTE_FLAG_ISFIRSTHOLD) ? true : false;
}

void a_rebote::process()
{
	switch (_state) {
	case E_BTN_WAIT_PRESS:
		// revisa si el tiempo termino para los multiples clicks
		if (_clicks != 0 && millis() - _clicksTimer >= 1000l) {
			_clicks = 0;
		}
		// espera que el usuario presione un boton
		if (readButtonPin()) {
			_debounceTimer = millis();
			_state = E_BTN_DEBOUNCE;
		}
		break;
	case E_BTN_DEBOUNCE:
		// Wait for debounce time...
		if (millis() - _debounceTimer >= (unsigned long) _debounceTimeSetting) {
			// and check if button is still pressed
			if (readButtonPin()) {
				// Clear held time
				_holdTime = 0;
				// Clear long press flag on each new button press
				_flags = _flags & ~A_REBOTE_FLAG_LONGPRESS;
				// Set pressed flag for polling API
				_flags = _flags | A_REBOTE_FLAG_al_presionar;
				// Set the "first hold" flag for the button hold event callback
				_flags = _flags | A_REBOTE_FLAG_ISFIRSTHOLD;
				// Start time counter for multiple clicks
				if (_clicks == 0)
					_clicksTimer = millis();
				// Increase button press counter
				_pressCount++;
				_clicks++;
				// Fire the onPress event
				if (cb_onPress) {
					cb_onPress(*this);
				}
				// Fire the multiple click event
				if (_clicks >= 2) {
					if (cb_onClick) {
						cb_onClick(*this);
					}
				}
				// Wait for button release
				_state = E_BTN_WAIT_RELEASE;
			} else {
				// False trigger (noise), wait for other pulse
				_state = E_BTN_WAIT_PRESS;
			}
		}
		break;
	case E_BTN_WAIT_RELEASE:
		// Check if button is being held
		if (readButtonPin()) {
			if (millis() - _debounceTimer >= (unsigned long) _holdTimeSetting) {
				_holdTime += millis() - _debounceTimer;
				_debounceTimer = millis();
				// Fire the onHold event
				if (cb_onHold) {
					cb_onHold(*this);
				}
				// Clear the first long press flag
				_flags = _flags & ~A_REBOTE_FLAG_ISFIRSTHOLD;
				_flags = _flags | A_REBOTE_FLAG_LONGPRESS;
			}
		} else {
			// Button release, wait for a new button press
			if (cb_onRelease) {
				cb_onRelease(*this);
			}
			_state = E_BTN_WAIT_PRESS;
		}
		break;
	default:
		_state = E_BTN_WAIT_PRESS;
		break;
	}
}

bool a_rebote::readButtonPin()
{
	int state = digitalRead(this->_pin);
	if (_mode == E_A_REBOTE_PULLUP || _mode == E_A_REBOTE_PULLUP_INTERNAL)
		return(state == LOW) ? true : false;
	else
		return(state == HIGH) ? true : false;
}
