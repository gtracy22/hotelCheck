#include <stdio.h>
#include <stdlib.h>

/* I defined all three possible room statuses */
typedef enum {
    STATUS_OPEN = 0,
    STATUS_OCCUPIED,
    STATUS_INVALID
} RoomStatus;

/* I created an array to store the status of all 40 rooms */
RoomStatus hotel[5][8];

/* I made every room open when the program starts */
void initHotel(void) {
    for (int f = 0; f < 5; f++) {
        for (int r = 0; r < 8; r++) {
            hotel[f][r] = STATUS_OPEN;
        }
    }
}

/*
 * I converted room numbers into array positions.
 * I checked that the floor and room number are valid.
 * I returned 1 for valid rooms and 0 for invalid rooms.
 */
int parseRoomNumber(int roomNum, int *floorIdx, int *roomIdx) {
    int floor = roomNum / 100;
    int room = roomNum % 100;

    if (floor < 1 || floor > 5 || room < 1 || room > 8) {
        return 0;
    }

    *floorIdx = floor - 1;
    *roomIdx = room - 1;
    return 1;
}

/* I converted room statuses into readable text */
const char* statusToString(RoomStatus status) {
    switch (status) {
        case STATUS_OPEN:     return "OPEN";
        case STATUS_OCCUPIED: return "OCCUPIED";
        case STATUS_INVALID:  return "INVALID / OUT OF SERVICE";
        default:              return "UNKNOWN";
    }
}

/* I displayed all rooms and their current statuses */
void displayAllRooms(void) {
    printf("\n================ HOTEL ROOM OVERVIEW ================\n");
    printf("Status Codes: [O] Open  |  [X] Occupied  |  [-] Invalid\n");
    printf("----------------------------------------------------\n");

    for (int f = 4; f >= 0; f--) {
        printf("Floor %d: ", f + 1);
        for (int r = 0; r < 8; r++) {
            int roomNum = (f + 1) * 100 + (r + 1);
            char code;
            switch (hotel[f][r]) {
                case STATUS_OPEN:     code = 'O'; break;
                case STATUS_OCCUPIED: code = 'X'; break;
                case STATUS_INVALID:  code = '-'; break;
            }
            printf("%d[%c]  ", roomNum, code);
        }
        printf("\n");
    }
    printf("====================================================\n");
}

/* I let the user check the status of a specific room */
void checkRoom(void) {
    int roomNum, f, r;
    printf("\nEnter room number to check (101-508): ");
    if (scanf("%d", &roomNum) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if (!parseRoomNumber(roomNum, &f, &r)) {
        printf("Room %d does not exist.\n", roomNum);
        return;
    }

    printf("Room %d status: %s\n", roomNum, statusToString(hotel[f][r]));
}

/* I let the user reserve a room if it is available */
void reserveRoom(void) {
    int roomNum, f, r;
    printf("\nEnter room number to reserve: ");
    if (scanf("%d", &roomNum) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if (!parseRoomNumber(roomNum, &f, &r)) {
        printf("Room %d does not exist.\n", roomNum);
        return;
    }

    if (hotel[f][r] == STATUS_OCCUPIED) {
        printf("Cannot reserve: Room %d is already occupied.\n", roomNum);
    } else if (hotel[f][r] == STATUS_INVALID) {
        printf("Cannot reserve: Room %d is currently out of service (invalid).\n", roomNum);
    } else {
        hotel[f][r] = STATUS_OCCUPIED;
        printf("Success: Room %d has been reserved.\n", roomNum);
    }
}

/* I let the user cancel a reservation and reopen the room */
void cancelRoom(void) {
    int roomNum, f, r;
    printf("\nEnter room number to cancel reservation: ");
    if (scanf("%d", &roomNum) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if (!parseRoomNumber(roomNum, &f, &r)) {
        printf("Room %d does not exist.\n", roomNum);
        return;
    }

    if (hotel[f][r] == STATUS_OPEN) {
        printf("Room %d is already open / not reserved.\n", roomNum);
    } else if (hotel[f][r] == STATUS_INVALID) {
        printf("Room %d is marked invalid, not currently occupied.\n", roomNum);
    } else {
        hotel[f][r] = STATUS_OPEN;
        printf("Success: Reservation for room %d has been cancelled. Room is now OPEN.\n", roomNum);
    }
}

/* I let the user mark a room out of service or restore it */
void toggleInvalidRoom(void) {
    int roomNum, f, r;
    printf("\nEnter room number to modify service validity: ");
    if (scanf("%d", &roomNum) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if (!parseRoomNumber(roomNum, &f, &r)) {
        printf("Room %d does not exist.\n", roomNum);
        return;
    }

    printf("Room %d is currently: %s\n", roomNum, statusToString(hotel[f][r]));
    printf("1. Set to INVALID (Out of order)\n");
    printf("2. Restore to OPEN\n");
    printf("Enter choice (1-2): ");

    int choice;
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        printf("Invalid input.\n");
        return;
    }

    if (choice == 1) {
        hotel[f][r] = STATUS_INVALID;
        printf("Room %d is now marked as INVALID.\n", roomNum);
    } else if (choice == 2) {
        hotel[f][r] = STATUS_OPEN;
        printf("Room %d has been restored to OPEN.\n", roomNum);
    } else {
        printf("Invalid selection.\n");
    }
}

int main(void) {
    initHotel();
    int choice;

    while (1) {
        printf("\n================ HOTEL MANAGEMENT ================\n");
        printf("1. View All Rooms\n");
        printf("2. Check a Specific Room\n");
        printf("3. Reserve a Room\n");
        printf("4. Cancel a Reservation (Free Room)\n");
        printf("5. Set Room as Invalid / Restore Room\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid selection. Please enter a number from 1 to 6.\n");
            continue;
        }

        switch (choice) {
            case 1:
                displayAllRooms();
                break;
            case 2:
                checkRoom();
                break;
            case 3:
                reserveRoom();
                break;
            case 4:
                cancelRoom();
                break;
            case 5:
                toggleInvalidRoom();
                break;
            case 6:
                printf("Exiting system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid selection. Please pick between 1 and 6.\n");
        }
    }

    return 0;
}
