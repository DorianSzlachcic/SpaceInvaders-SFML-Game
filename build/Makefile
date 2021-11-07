objects = BigSlowEnemy.o Enemy.o Funcs.o Laser.o Main.o NormalEnemy.o Player.o Points.o SmallFastEnemy.o SoundManager.o
includeFlag = -I/home/dorian/SFML/include
libFlag = -L/home/dorian/SFML/lib
modulesFlag = -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

output: $(objects)
	g++ $(libFlag) *.o -o SpaceInvaders $(modulesFlag)
	cp -r ../textures .
	cp -r ../sounds .

$(objects): %.o: ../src/%.cpp
	g++ $(includeFlag) -c $< -o $@

run: output
	./SpaceInvaders

clean:
	rm -rf *.o output textures sounds