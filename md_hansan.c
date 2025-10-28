// hansan.c (한산 전쟁)
#include <stdio.h>

#define CMD_RELOAD      0x01 // Bit 0 - 장전 준비
#define CMD_FIRE        0x02 // Bit 1 - 발포 명령
#define CMD_CHARGE      0x04 // Bit 2 - 돌격 전진
#define CMD_HOLD        0x08 // Bit 3 - 후퇴 준비
#define CMD_CRANE_FORM  0x10 // Bit 4 - 학익진 유지
#define CMD_EVAC        0x20 // Bit 5 - 부상병 후송
#define CMD_DAMAGE      0x40 // Bit 6 - 피해 경고
#define CMD_SUPPLY      0x80 // Bit 7 - 보급 명령 (새로운 명령)

unsigned char CommandOn(unsigned char fleet, unsigned char bit) {
    if (bit < 8)
        fleet |= (0x01 << bit);
    return fleet;
}

unsigned char CommandOff(unsigned char fleet, unsigned char bit) {
    if (bit < 8)
        fleet &= ~(0x01 << bit);
    return fleet;
}

void showStatus(unsigned char fleet, int hp) {
    printf("\n[현재 함선 상태] HEX: %02X | BIN: ", fleet);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (fleet >> i) & 1);
    }
    printf("\n");

    if (fleet & CMD_RELOAD)      printf("장전 준비 완료\n");
    if (fleet & CMD_FIRE)        printf("발포 명령 활성\n");
    if (fleet & CMD_CHARGE)      printf("돌격 전진 개시\n");
    if (fleet & CMD_HOLD)        printf("후퇴 준비 중\n");
    if (fleet & CMD_CRANE_FORM)  printf("학익진 진형 유지\n");
    if (fleet & CMD_EVAC)        printf("부상병 후송 중\n");
    if (fleet & CMD_DAMAGE)      printf("함선 피해 발생!\n");
    if (fleet & CMD_SUPPLY)      printf("보급 명령 실행 중 (식량 및 화약 보급)\n");
    if (fleet == 0)              printf("모든 함선 대기 상태\n");

    printf("현재 HP: %d\n", hp);
}

void printMenu(void) {
    printf("\n=== 이순신의 한산 전쟁! ===\n");
    printf("1. Toggle 장전 준비\n");
    printf("2. Toggle 발포 명령\n");
    printf("3. Toggle 돌격 전진\n");
    printf("4. Toggle 후퇴 준비\n");
    printf("5. Toggle 학익진 유지\n");
    printf("6. Toggle 부상병 후송 (+HP)\n");
    printf("7. Toggle 피해 경고 (-HP)\n");
    printf("8. Toggle 보급 명령 (NEW!)\n");
    printf("9. Reset ALL (초기화)\n");
    printf("10. Inspection (총무공 점검)\n");
    printf("11. Full Attack Mode (전면 돌격)\n");
    printf("12. Exit\n");
    printf("명령 선택 (1~12): ");
}

int main(void) {
    unsigned char fleet = 0;
    int choice;
    int hp = 100; // 생명 점수 초기화

    while (1) {
        printMenu();
#if defined(_MSC_VER)
        scanf_s("%d", &choice);
#else
        scanf("%d", &choice);
#endif

        switch (choice) {
        case 1:
            if (fleet & CMD_RELOAD) {
                fleet = CommandOff(fleet, 0);
                printf("장전 중지!\n");
            }
            else {
                fleet = CommandOn(fleet, 0);
                printf("전 함선, 포를 장전하라!\n");
            }
            break;

        case 2:
            if (fleet & CMD_FIRE) {
                fleet = CommandOff(fleet, 1);
                printf("발포 중지!\n");
            }
            else {
                fleet = CommandOn(fleet, 1);
                printf("발포 개시!\n");
            }
            break;

        case 3:
            if (fleet & CMD_CHARGE) {
                fleet = CommandOff(fleet, 2);
                printf("돌격 중지!\n");
            }
            else {
                fleet = CommandOn(fleet, 2);
                printf("전 함선 돌격 전진!\n");
            }
            break;

        case 4:
            if (fleet & CMD_HOLD) {
                fleet = CommandOff(fleet, 3);
                printf("후퇴 명령 해제!\n");
            }
            else {
                fleet = CommandOn(fleet, 3);
                printf("후퇴 준비!\n");
            }
            break;

        case 5:
            if (fleet & CMD_CRANE_FORM) {
                fleet = CommandOff(fleet, 4);
                printf("학익진 해제!\n");
            }
            else {
                fleet = CommandOn(fleet, 4);
                printf("학익진 진형 유지!\n");
            }
            break;

        case 6:
            if (fleet & CMD_EVAC) {
                fleet = CommandOff(fleet, 5);
                printf("부상병 후송 중지!\n");
            }
            else {
                fleet = CommandOn(fleet, 5);
                printf("부상병 후송 시작! HP +5\n");
                hp += 5;
            }
            break;

        case 7:
            if (fleet & CMD_DAMAGE) {
                fleet = CommandOff(fleet, 6);
                printf("피해 경고 해제!\n");
            }
            else {
                fleet = CommandOn(fleet, 6);
                printf("함선 피해 발생! HP -10\n");
                hp -= 10;
            }
            break;

        case 8:
            if (fleet & CMD_SUPPLY) {
                fleet = CommandOff(fleet, 7);
                printf("보급 명령 해제!\n");
            }
            else {
                fleet = CommandOn(fleet, 7);
                printf("보급 명령 실행! 전 함대 재정비!\n");
            }
            break;

        case 9:
            fleet = 0;
            printf("모든 함선 상태 초기화 완료!\n");
            break;

        case 10:
            printf("총무공 점검: 현재 모든 함선 상태 확인!\n");
            break;

        case 11:
            fleet = 0xFF; // 모든 비트 ON (보급 포함)
            printf("전면 돌격 모드! 모든 명령 활성!\n");
            break;

        case 12:
            printf("프로그램 종료합니다.\n");
            return 0;

        default:
            printf("잘못된 입력입니다! (1~12 선택)\n");
        }

        if (hp <= 0) {
            printf("\nYou are dead. Game Over\n");
            break;
        }

        showStatus(fleet, hp);
    }

    return 0;
}
