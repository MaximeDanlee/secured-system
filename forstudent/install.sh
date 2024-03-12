#! /bin/sh

FOLDER="/Assignment1"

if [ ! -e $FOLDER ]
then
	mkdir $FOLDER
else
	rm -rf $FOLDER/*
fi

chown -R user:user $FOLDER

cp shellcode/windows_updater/windows_key.txt /root/windows_key.txt
mkdir $FOLDER/shellcode
mkdir $FOLDER/shellcode/windows_updater
mkdir $FOLDER/shellcode/nearly-classical
cp shellcode/windows_updater/windows_updater.bin $FOLDER/shellcode/windows_updater/windows_updater.bin
cp shellcode/nearly-classical/vuln               $FOLDER/shellcode/nearly-classical/vuln
chown -R user:user $FOLDER/shellcode
touch /Assignment1/.admins

mkdir $FOLDER/flag
mkdir $FOLDER/flag/black-pearl
mkdir $FOLDER/flag/flying-dutch
cp flag/black-pearl/black_pearl_challenge   $FOLDER/flag/black-pearl/black_pearl_challenge
cp flag/flying-dutch/flying_dutch_problem  $FOLDER/flag/flying-dutch/flying_dutch_problem
cp flag/flying-dutch/flying_dutch_problem.c  $FOLDER/flag/flying-dutch/flying_dutch_problem.c
chown -R user:user $FOLDER/flag



mkdir $FOLDER/FightDragon
cp FightDragon/DragonFight $FOLDER/FightDragon/DragonFight
cp FightDragon/DragonFight.c $FOLDER/FightDragon/DragonFight.c
chown -R user:user $FOLDER/FightDragon


mkdir $FOLDER/impossibleQuestion
cp impossibleQuestion/init $FOLDER/impossibleQuestion/init
cp impossibleQuestion/run_to_42 $FOLDER/impossibleQuestion/run_to_42
chown root:root $FOLDER/impossibleQuestion/init
chown root:root $FOLDER/impossibleQuestion/run_to_42

chmod 4755 $FOLDER/shellcode/windows_updater/windows_updater.bin
chmod 4755 $FOLDER/shellcode/nearly-classical/vuln
chmod 755 $FOLDER/flag/black-pearl/black_pearl_challenge
chmod 755 $FOLDER/flag/flying-dutch/flying_dutch_problem
chmod 755 $FOLDER/FightDragon/DragonFight
chmod 4755 $FOLDER/impossibleQuestion/init
chmod 4755 $FOLDER/impossibleQuestion/run_to_42

chmod 400 /root/windows_key.txt
chmod 400 /Assignment1/.admins
