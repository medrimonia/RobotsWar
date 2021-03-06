      _____       _           _    __          __        
     |  __ \     | |         | |   \ \        / /        
     | |__) |___ | |__   ___ | |_ __\ \  /\  / /_ _ _ __ 
     |  _  // _ \| '_ \ / _ \| __/ __\ \/  \/ / _` | '__|
     | | \ \ (_) | |_) | (_) | |_\__ \\  /\  / (_| | |   
     |_|  \_\___/|_.__/ \___/ \__|___/ \/  \/ \__,_|_|   
                                                         
     
by Robot Campus
[http://www.robotcampus.fr/](http://www.robotcampus.fr/)


Installation
------------

    sudo aptitude install build-essential git-core wget screen dfu-util \
        openocd python python-serial

Directories
-----------

* `BinutilsArm/`: Contains all tools to compile and play with ARM architecture
* `LibMaple/`: Contains libmaple source files, this is the
  [modified fork of RobotCampus](https://github.com/RobotsWar/libmaple)
* `LibRobotCampus/`: Contains Robot Campus own helpers
* `skeleton/`: A skeleton boilerplate, just copy and paste it to `src/` or the
  name you want to create a new project (see below)
* `joypad/`: contains some scripts to send commands to your robots using joypads

Compilation
-----------

- Copy `skeleton/` to `src/`, for instance
- Write your code in `src/`
- Update the first line of `build-targets.mk` if you want to add some files
- In `src/`, run `make` to compile
- In `src/`, run `make install` to flash your board

32-bits compatibilities
-----------------------

The arm binutils are 32-bits, if you are on a 64-bits system and want compatibility,
you can try:

```
dpkg --add-architecture i386
apt-get update
apt-get install ia32-libs
```

Documentation
-------------

* [libmaple documentation](http://leaflabs.com/docs/)
* [Maple Mini specifications](http://leaflabs.com/docs/hardware/maple-mini.html)

