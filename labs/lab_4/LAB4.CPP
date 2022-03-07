#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>



// Bohemian Rapsody
unsigned int notes_1[] = { 233,350,466,587,783,698};
unsigned int note_delay[] = {400,400,400,400,800,800};
unsigned int notes_2[] = {294,294,233,262,294,294,262,294,311,350,311,294,262,262,294,311,350,311,294,262};
unsigned int note_delay_2[] = {800,800,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,800};

void PlaySound();
void StateWords();
void CharToBin(unsigned char state, char* str);
void TurnSpeaker(int isActive);
void SetCount(int iDivider);
void Menu();

int main() {	
	Menu();
	return 0;
}

void Menu() {
	int choice = 0;
	while (1) {
		system("cls");
		printf("1 - Play sound");
		printf("\n2 - Print channels state words");
		printf("\n0 - Exit");
		
		printf("\n\nEnter choice: ");
		scanf("%d", &choice);
		if(choice >= 0 && choice <= 2) {
			switch (choice) {
				case 0:
					return;
					
				case 1:
					PlaySound();
				break;
				
				case 2:
					StateWords();
					printf("\n\nPress any key to continue: ");
					scanf("%d", &choice);
				break;
			}
		}
	}
}

void StateWords()
{
    // port 40h (channel 0, system clock interrupion)
    // port 41h (channel 1, memory regeneration)
    // port 42h (channel 2, speaker sound)
	int channel, state;
	char stateWord[8];
	int ports[] = {0x40, 0x41, 0x42};
	int controlWord[] = {226, 228, 232};     // 11 10 001 0, 11 10 010 0, 11 10 100 0	 
											//       --1          -1-          1--
	printf("\nStatus word: \n");

	for (channel = 0; channel < 3; channel++)
    {
		outp(0x43, controlWord[channel]);    // select channel (CLC commands)
		state = inp(ports[channel]);         // read state
	
		for (int i = 7; i >= 0; i--)         // make binary
        {
			stateWord[i] = state % 2 + '0';
			state /= 2;
		}

		printf("\nChannel %d: ", channel);
		for (i = 0; i < 8;  i++) 
			printf("%c", stateWord[i]);
		printf("\n");
	}
}
void SetCount(int iDivider) {
	long base = 1193180;    // IRQ 18.2 times per second (1.19 MHz)
	long kd;
	outp(0x43, 0xB6);      // 10110110 - channel 2 , operation 4 (read/write low after high), mode 3 (Square wave), format 0 (bynaric)
	kd = base / iDivider; 
	outp(0x42, kd % 256); // (low) the smallest byte of the frequency divider 
	kd /= 256;
	outp(0x42, kd);      // (high) the highest byte of the frequency divider 
	return;
}
void TurnSpeaker(int isActive) { // turn on/off speakers
	if (isActive) {
		outp(0x61, inp(0x61) | 3); //set 2 low bits 11
		return;
	} else {
		outp(0x61, inp(0x61) & 0xFC); // set  2 low bits 00
		return;
	}
}

void PlaySound() { // all song will be in future :3
	for (int i = 0; i < 12; i++) { 
		SetCount(notes_1[i%6]);
		TurnSpeaker(1);               // turn on speakers
		delay(note_delay[i%6]);      // set duration of note (in ms)
		TurnSpeaker(0);             // turn off speakers
	}
		for (int j = 0; j < 20; j++) {
		SetCount(notes_2[j]);
		TurnSpeaker(1);
		delay(note_delay_2[j]);
		TurnSpeaker(0);
	}
}
