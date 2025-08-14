target_include_directories(Paratroopers PRIVATE include)

target_sources(Paratroopers PRIVATE src/Airplane.cpp src/Arena.cpp src/BaseObject.cpp src/Bomb.cpp src/Bullet.cpp sfx/fire.c sfx/destroy.c src/Cannon.cpp src/Helicopter.cpp src/Paratrooper.cpp src/Phase.cpp src/PhaseData.cpp src/Ufo.cpp sfx/missile.c sfx/flyby.c sfx/pass.c sfx/jump.c sfx/falling.c sfx/et.c)
