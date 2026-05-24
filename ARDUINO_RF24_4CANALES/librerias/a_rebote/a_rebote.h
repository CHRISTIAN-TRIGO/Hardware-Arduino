/* 
 ********  ING.LUIS ENRIQUE DE LA TORRE VERA  ***************************
 *****CENTRO DE SISTEMASS DE COMPUTO Y ELECTRONICA ********************
*/
#ifndef A_REBOTE_H
#define A_REBOTE_H

/*-------------------------------------------------------------*/
/*		Includes and dependencies			*/
/*-------------------------------------------------------------*/
#include <Arduino.h>

/*-------------------------------------------------------------*/
/*		Macros and definitions				*/
/*-------------------------------------------------------------*/
#define A_REBOTE_FLAG_LONGPRESS		0x01
#define A_REBOTE_FLAG_al_presionar	0x02
#define A_REBOTE_FLAG_ISFIRSTHOLD	0x04

/*-------------------------------------------------------------*/
/*		Typedefs enums & structs			*/
/*-------------------------------------------------------------*/

/**
 * Class pre-declaration
 */
class a_rebote;

/**
 * Typedef for callback function pointers
 */
typedef void (* a_reboteEventHandler_t)(a_rebote &);

/**
 * Defines the button FSM states
 */
enum buttonstates {
	/**
	 * FSM is waiting for button press
	 */
	E_BTN_WAIT_PRESS,

	/**
	 * FSM is on debouncing state
	 */
	E_BTN_DEBOUNCE,

	/**
	 * FSM is waiting for button release
	 */
	E_BTN_WAIT_RELEASE,
};

/**
 * Defines the button operating modes according to hardware connections
 */
enum buttonmodes {
	/**
	 * Button with active LOW mode, external pullup
	 */
	E_A_REBOTE_PULLUP,

	/**
	 * Button with active LOW mode, use internal pullup
	 */
	E_A_REBOTE_PULLUP_INTERNAL,

	/**
	 * Button with active HIGH mode, use external pulldown
	 */
	E_A_REBOTE_PULLDOWN,
};

/*-------------------------------------------------------------*/
/*		Class definition				*/

/*-------------------------------------------------------------*/
class a_rebote {
public:
	/*-------------------------------------------------------------*/
	/*		Class methods and constructors			*/
	/*-------------------------------------------------------------*/

	/**
	 * Class constructor, creates an instance of A_REBOTE class
	 * 
	 * @param pin Pin number assigned to button
	 * @param mode Operating mode of the button: E_A_REBOTE_PULLUP,
	 * E_A_REBOTE_PULLUP_INTERNAL or E_A_REBOTE_PULLDOWN
	 */
	a_rebote(uint8_t pin, uint8_t mode = E_A_REBOTE_PULLUP_INTERNAL);

	/**
	 * Sets the time needed to trigger the hold event
	 * 
	 * Default time is 5 seconds but can be changed using this method.
	 * 
	 * @param time The time the button needs to be pressed to trigger the
	 * hold event.
	 */
	void setHoldTime(uint16_t time);

	/**
	 * Sets the debounce process time
	 * 
	 * Default time is 20 ms but can be changed using this method.
	 * 
	 * @param time The time used to debounce the button.
	 */
	void setDebounceTime(uint16_t time);

	/**
	 * Configures the button press event
	 * 
	 * This method sets the callback for the press event of the button
	 * 
	 * @param handler Pointer to a function that handles the event
	 */
	void setPressHandler(a_reboteEventHandler_t handler);

	/**
	 * Configures the button hold event
	 * 
	 * This method sets the callback for the hold event of the button
	 * 
	 * @param Pointer to a function that handles the event
	 */
	void setHoldHandler(a_reboteEventHandler_t handler);

	/**
	 * Configures the button release event
	 * 
	 * This method sets the callback for the release event of the button
	 * 
	 * @param Pointer to a function that handles the event
	 */
	void setReleaseHandler(a_reboteEventHandler_t handler);

	/**
	 * Configures the button click event
	 * 
	 * This method sets the callbacl for the click event of the button
	 * 
	 * @param Pointer to a function that handles the event
	 */
	void setClicksHandler(a_reboteEventHandler_t handler);

	/**
	 * Gets the pin number associated to the instance
	 * 
	 * @returns The pin number
	 */
	uint8_t getPin();

	/**
	 * Gets the number of times the button has been pressed since the
	 * creation of the object.
	 * 
	 * @returns The number of clicks since object creation
	 */
	uint16_t getPressCount();

	/**
	 * Gets the time the button has been held pressed in milliseconds 
	 * 
	 * @returns The time in milliseconds that the button has been pressed
	 */
	uint16_t getHoldTime();

	/**
	 *  Gets the click count when multiclick event is triggered
	 * 
	 * @returns The number of clicks given when multiclick event is
	 * triggered
	 */
	uint16_t getClicks();

	/**
	 * Checks if button is currently pressed, returns true while the button
	 * is held.
	 * 
	 * @returns True while the button is pressed, false when it´s released
	 */
	bool Consecutivo();

	/**
	 * Checks if the button was pressed, calling this function clears the
	 * flag so a second call would return false until the button is released
	 * and then pressed again.
	 * 
	 * @returns True if the button is or was pressed and false if it has not
	 * been pressed. This method returns true only on the first call, after
	 * that, it will return false until the button is released and pressed
	 * again. 
	 */
	bool al_presionar();

	/**
	 * Check if the latest button press was a long press (button hold)
	 * 
	 * @returns True if the last button press was a long one. Returns false
	 * otherwise.
	 */
	bool wasLongPress();

	/**
	 * TO BE USED INSIDE THE HOLD CALLBACK. Checks if this is the first call
	 * to the hold event callback.
	 * 
	 * @returns True if the callback being invoked was the first one for the
	 * hold event.
	 */
	bool isFirstHold();

	/**
	 * Main class processing method
	 * 
	 * This methods checks the button pin for changes and issues all the
	 * callbacks. Should be called frequently inside the main program loop
	 */
	void process();

private:
	/**
	 * Stores the state of the button FSM
	 */
	enum buttonstates _state = E_BTN_WAIT_PRESS;

	/**
	 * Button mode: pull-up, internal pull-up, pull-down
	 */
	uint8_t _mode;

	/**
	 * The pin number where the button is connected
	 */
	uint8_t _pin;

	/**
	 * Time threshold for button hold event
	 */
	uint16_t _holdTimeSetting;

	/**
	 * Configuration for debounce duration
	 */
	uint16_t _debounceTimeSetting;

	/**
	 * The button press counter, total button press count
	 */
	uint16_t _pressCount;

	/**
	 * The ammount of time (in milliseconds) the button has been held pressed.
	 */
	uint16_t _holdTime;

	/**
	 * The button click count inside the multiple click time frame
	 * Multiple clicks should occur within one second.
	 */
	uint16_t _clicks;

	/**
	 * Debounce timer
	 */
	uint32_t _debounceTimer;

	/**
	 * Timer for multiple clicks
	 */
	uint32_t _clicksTimer;

	/**
	 * Pointer for "on press" event callback
	 */
	a_reboteEventHandler_t cb_onPress;

	/**
	 * Pointer for "on hold" event 
	 */
	a_reboteEventHandler_t cb_onHold;

	/**
	 * Pointer for "on release" event callback
	 */
	a_reboteEventHandler_t cb_onRelease;

	/**
	 * Pointer for "on clicks" event 
	 */
	a_reboteEventHandler_t cb_onClick;

	/**
	 * Status flags variable
	 */
	uint8_t _flags;

	/**
	 * Private method to determine if the button is being actuated
	 */
	bool readButtonPin();
};

#endif
