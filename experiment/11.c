#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct song {
    int id;
    char title[100];
    char artist[50];
    char filepath[300];
    struct song* next;
} Song;

typedef struct playlistmanager {
    Song* head;
    Song* tail;
    Song* current;
} PlaylistManager;

// 播放音乐 (Windows)
void play_audio_windows(const char* filename) {
    char command[256];
    snprintf(command, sizeof(command), "start \"\" \"%s\"", filename);
    int ret = system(command);
    if (ret != 0) {
        printf("播放失败，请检查文件是否存在或格式是否支持。\n");
    }
}

// 从 song_list.txt 读取歌曲信息，创建链表
int load_records_createNode(PlaylistManager* playlistmanager) {
    Song* head = (Song*)malloc(sizeof(Song));
    if (head == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }

    head->id = 0;
    head->next = NULL;

    FILE* fp = fopen("song_list.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件！\n");
        free(head);
        return 0;
    }

    Song* p = head;
    int count = 0;

    while (1) {
        Song temp;
        if (fscanf(fp, "%d,%99s,%49s,%299s", &temp.id, temp.title, temp.artist, temp.filepath) != 4) {
            break; // 读到末尾或格式错误
        }

        Song* node = (Song*)malloc(sizeof(Song));
        if (!node) {
            printf("内存分配失败！\n");
            break;
        }

        *node = temp;
        node->next = NULL;
        p->next = node;
        p = node;
        count++;
    }

    fclose(fp);
    playlistmanager->head = head;
    playlistmanager->tail = (count == 0) ? head : p;
    playlistmanager->current = head->next ? head->next : head;
    return count;
}

// 手动添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, const char* filepath) {
    manager->tail->next = (Song*)malloc(sizeof(Song));
    if (manager->tail->next == NULL) {
        printf("内存分配失败！");
        return;
    }
    Song* p = manager->tail->next;
    p->id = (manager->tail == manager->head) ? 1 : manager->tail->id + 1;
    strncpy(p->title, title, sizeof(p->title) - 1);
    p->title[sizeof(p->title) - 1] = '\0';
    strncpy(p->artist, artist, sizeof(p->artist) - 1);
    p->artist[sizeof(p->artist) - 1] = '\0';
    strncpy(p->filepath, filepath, sizeof(p->filepath) - 1);
    p->filepath[sizeof(p->filepath) - 1] = '\0';
    p->next = NULL;
    manager->tail = p; // 更新尾指针

    FILE* fp = fopen("song_list.txt", "a");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return;
    }
    fprintf(fp, "%d,%s,%s,%s\n", p->id, p->title, p->artist, p->filepath);
    fclose(fp);
}

// 显示播放列表
void display_playlist(PlaylistManager* manager) {
    Song* p = manager->head->next;
    if (p == NULL) {
        printf("播放列表为空！\n");
        return;
    }
    printf("播放列表：\n");
    while (p != NULL) {
        printf("标题: %s, 歌手: %s, 文件路径: %s\n", p->title, p->artist, p->filepath);
        p = p->next;
    }
}

// 删除歌曲（按标题）
int delete_song(PlaylistManager* manager, const char* title) {
    Song* p = manager->head;
    while (p->next != NULL) {
        if (strcmp(p->next->title, title) == 0) {
            Song* temp = p->next;
            p->next = p->next->next;
            if (temp == manager->tail) {
                manager->tail = p; // 更新尾指针
            }
            free(temp);
            return 1; // 删除成功
        }
        p = p->next;
    }
    return 0; // 未找到该歌曲
}

// 播放歌曲（按标题）
int play_song(PlaylistManager* manager, const char* title) {
    Song* p = manager->head->next;
    while (p != NULL) {
        if (strcmp(p->title, title) == 0) {
            printf("正在播放: %s by %s\n", p->title, p->artist);
            play_audio_windows(p->filepath);
            return 1; // 播放成功
        }
        p = p->next;
    }
    return 0; // 未找到该歌曲
}

// 导出歌单
void export_playlist(PlaylistManager* manager, char* filepath) {
    FILE* fp = fopen(filepath, "w");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return;
    }
    Song* p = manager->head->next;
    while (p != NULL) {
        fprintf(fp, "%d,%s,%s,%s\n", p->id, p->title, p->artist, p->filepath);
        p = p->next;
    }
    fclose(fp);
    printf("播放列表已导出到 %s\n", filepath);
}

// 随机播放音乐
void play_song_random(PlaylistManager* manager) {
    Song* p = manager->head->next;
    if (p == NULL) {
        printf("播放列表为空！\n");
        return;
    }
    int count = 0;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    int random_index = rand() % count;
    p = manager->head->next;
    for (int i = 0; i < random_index; i++) {
        p = p->next;
    }
    printf("随机播放: %s by %s\n", p->title, p->artist);
    play_audio_windows(p->filepath);
}

// 在指定位置添加歌曲
int insert_song_at(PlaylistManager* manager, int position, const char* title, const char* artist, const char* filepath) {
    if (position < 0) {
        return 0; // 无效位置
    }
    Song* p = manager->head;
    for (int i = 0; i < position; i++) {
        if (p->next == NULL) {
            return 0; // 位置超出范围
        }
        p = p->next;
    }
    Song* new_song = (Song*)malloc(sizeof(Song));
    if (new_song == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }
    new_song->id = (p == manager->head) ? 1 : p->id + 1;
    strncpy(new_song->title, title, sizeof(new_song->title) - 1);
    new_song->title[sizeof(new_song->title) - 1] = '\0';
    strncpy(new_song->artist, artist, sizeof(new_song->artist) - 1);
    new_song->artist[sizeof(new_song->artist) - 1] = '\0';
    strncpy(new_song->filepath, filepath, sizeof(new_song->filepath) - 1);
    new_song->filepath[sizeof(new_song->filepath) - 1] = '\0';
    new_song->next = p->next;
    p->next = new_song;
    if (new_song->next == NULL) {
        manager->tail = new_song; // 更新尾指针
    }
    return 1; // 插入成功
}

// 清空播放列表
void clear_playlist(PlaylistManager* manager) {
    Song* p = manager->head->next;
    while (p != NULL) {
        Song* temp = p;
        p = p->next;
        free(temp);
    }
    manager->head->next = NULL;
    manager->tail = manager->head;
    manager->current = manager->head;
}

// 打印操作菜单
void printcontent();

int main() {
    int choice, count = 0;
    PlaylistManager playlistmanager = {0};
    srand((unsigned int)time(NULL));
    if (!(count = load_records_createNode(&playlistmanager))) {
        printf("加载歌曲失败！\n");
        return 0;
    }

    while (1) {
        printcontent();
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                char title[100];
                char artist[50];
                char filepath[300];
                printf("请输入歌曲标题：");
                scanf("%99s", title);
                printf("请输入歌手名称：");
                scanf("%49s", artist);
                printf("请输入文件路径：");
                scanf("%299s", filepath);
                add_song(&playlistmanager, title, artist, filepath);
                break;
            }
            case 2: {
                display_playlist(&playlistmanager);
                break;
            }
            case 3: {
                char title[100];
                printf("请输入要删除的歌曲标题：");
                scanf("%99s", title);
                if (delete_song(&playlistmanager, title)) {
                    printf("歌曲删除成功！\n");
                } else {
                    printf("未找到该歌曲！\n");
                }
                break;
            }
            case 4: {
                char title[100];
                printf("请输入要播放的歌曲标题：");
                scanf("%99s", title);
                if (play_song(&playlistmanager, title)) {
                    printf("歌曲播放成功！\n");
                } else {
                    printf("未找到该歌曲！\n");
                }
                break;
            }
            case 5: {
                char filepath[300];
                printf("请输入导出文件路径：");
                scanf("%299s", filepath);
                export_playlist(&playlistmanager, filepath);
                break;
            }
            case 6: {
                play_song_random(&playlistmanager);
                break;
            }
            case 7: {
                int position;
                char title[100];
                char artist[50];
                char filepath[300];
                printf("请输入插入位置（从0开始）：");
                scanf("%d", &position);
                printf("请输入歌曲标题：");
                scanf("%99s", title);
                printf("请输入歌手名称：");
                scanf("%49s", artist);
                printf("请输入文件路径：");
                scanf("%299s", filepath);
                if (insert_song_at(&playlistmanager, position, title, artist, filepath)) {
                    printf("歌曲插入成功！\n");
                } else {
                    printf("插入位置无效！\n");
                }
                break;
            }
            case 8: {
                clear_playlist(&playlistmanager);
                printf("播放列表已清空！\n");
                break;
            }
            case 0: {
                printf("退出程序！\n");
                exit(0);
            }
        }
    }
    return 0;
}

void printcontent() {
    printf("链表音乐播放器管理器");
    printf("\n==========================================\n");
    printf("1.人工添加歌曲\n");
    printf("2.显示播放列表\n");
    printf("3.删除歌曲（按标题）\n");
    printf("4.播放歌曲（按标题）\n");
    printf("5.导出歌单\n");
    printf("6.随机播放歌曲\n");
    printf("7.在指定位置添加歌曲\n");
    printf("8.清空播放列表\n");
    printf("0.退出程序\n");
    printf("==========================================\n");
    printf("请选择操作（0-8）：");
}