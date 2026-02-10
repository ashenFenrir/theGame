#ifndef WINDOW_EVENTS_H_
#define WINDOW_EVENTS_H_

typedef unsigned int uint;

class Events {
public:
	static bool* _keys;
	static uint* _frames;
	static uint _current;
	static float deltaX;
	static float deltaY;
	static float _x;
	static float _y;
	static bool _cursor_locked;
	static bool _cursor_started;
    static bool _quit;

	static bool init();
	static void pullEvents();

	static bool pressed(int keycode);
	static bool jpressed(int keycode);

	static bool clicked(int button);
	static bool jclicked(int button);

	//static void toogleCursor();

    static bool isQuit();
};

#endif /* WINDOW_EVENTS_H_ */