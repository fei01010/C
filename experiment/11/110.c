#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 歌曲节点结构体
typedef struct Song {
    int id;
    char title[100];
    char artist[50];
    char filepath[300];
    struct Song* next;
} Song;

// 播放列表管理器
typedef struct PlaylistManager{
    Song* head;
    Song* tail;
    Song* current;
    int song_count;
} PlaylistManager;

// 函数声明
void init_playlist_manager(PlaylistManager* manager);                           // 初始化链表
int load_songs_from_file(PlaylistManager* manager, const char* filename);       // 从文件中读取到链表
void add_song(PlaylistManager* manager, const char* title, const char* artist,  // 人工增加音乐
              const char* filepath);
void display_playlist(PlaylistManager* manager);                                // 显示播放列表
int delete_songs_by_title(PlaylistManager* manager, const char* title);         // 删除指定名字的音乐
int play_song_by_title(PlaylistManager* manager, const char* title);            // 根据名字播放音乐
int export_playlist(PlaylistManager* manager, const char* filename);            // 导出播放列表
int play_song_random(PlaylistManager* manager);                                 // 随机播放音乐
int insert_song_at(PlaylistManager* manager, int position, const char* title, const char* artist, const char* filepath);    // 向指定位置添加音乐
void destroy_playlist(PlaylistManager* manager);                                // 清空列表

// linux/Mac 版本
// void play_audio(const char* filename) {
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Founded File!!");
//     }
//     snprintf(command, sizeof(command), "afplay \"%s\"", filename);
//     int ret = system(command);
//     if (ret != 0) {
//         printf("播放失败或中断，请检查文件格式是否支持。\n");
//     }
// }

// Windows 版本
void play_audio(const char* filename){
    char command[256];
    FILE *mp3File = fopen(filename, "rb");
    if (!mp3File) {
        printf("无法打开文件 %s\n", filename);
        return;
    }
    else{
        printf("Founded File!!");
    }
    snprintf(command, sizeof(command), "start \"\" \"%s\"", filename);
    int ret = system(command);
    if (ret != 0) {
        printf("播放失败或中断，请检查文件格式是否支持。\n");
    }
    
    // 或者使用 Windows Media Player
    // sprintf(command, "wmplayer \"%s\"", filename);
    // system(command);
}


int load_songs_from_file(PlaylistManager* manager, const char* filename){
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }

    int count = 0;
    while (1) {
        Song temp;
        if (fscanf(fp, "%d,%99[^,],%49[^,],%299[^\n]", &temp.id, temp.title, temp.artist, temp.filepath) != 4) {
            break; // 读到末尾或格式不符
        }

        Song* node = (Song*)malloc(sizeof(Song));
        if (!node) {
            printf("内存分配失败！\n");
            break;
        }
        *node = temp;
        node->next = NULL;

        if (manager->head == NULL) {
            manager->head = node;
            manager->tail = node;
        } else {
            manager->tail->next = node;
            manager->tail = node;
        }
        manager->song_count++;
        count++;
    }

    fclose(fp);
    return count;
}


// 初始化播放管理器
void init_playlist_manager(PlaylistManager* manager){
    manager->head = NULL;
    manager->tail = NULL;
    manager->current = NULL;
    manager->song_count = 0;
}

// 1. 在链表末尾添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, 
              const char* filepath) {
    Song* node = (Song*)malloc(sizeof(Song));
    if (!node) {
        printf("内存分配失败！\n");
        return;
    }

    node->id = (manager->tail == NULL) ? 1 : manager->tail->id + 1;
    strncpy(node->title, title, sizeof(node->title) - 1);
    node->title[sizeof(node->title) - 1] = '\0';
    strncpy(node->artist, artist, sizeof(node->artist) - 1);
    node->artist[sizeof(node->artist) - 1] = '\0';
    strncpy(node->filepath, filepath, sizeof(node->filepath) - 1);
    node->filepath[sizeof(node->filepath) - 1] = '\0';
    node->next = NULL;

    if (manager->head == NULL) {
        manager->head = node;
        manager->tail = node;
    } else {
        manager->tail->next = node;
        manager->tail = node;
    }

    manager->song_count++;
    printf("已添加歌曲: %s by %s\n", node->title, node->artist);
}

// 2. 显示播放列表
void display_playlist(PlaylistManager* manager) {
    if (manager->head == NULL) {
        printf("播放列表为空\n");
        return;
    }
    Song* p = manager->head;
    printf("当前播放列表(共 %d 首):\n", manager->song_count);
    while (p != NULL) {
        printf("ID:%d | 标题:%s | 歌手:%s | 路径:%s\n", p->id, p->title, p->artist, p->filepath);
        p = p->next;
    }
}

// 3. 删除歌曲
int delete_songs_by_title(PlaylistManager* manager, const char* title) {
    if (manager->head == NULL) return 0;

    int removed = 0;
    Song* prev = NULL;
    Song* cur = manager->head;

    while (cur != NULL) {
        if (strcmp(cur->title, title) == 0) {
            Song* to_delete = cur;
            if (prev == NULL) {
                manager->head = cur->next;
            } else {
                prev->next = cur->next;
            }
            if (cur == manager->tail) {
                manager->tail = prev;
            }
            cur = cur->next;
            free(to_delete);
            manager->song_count--;
            removed++;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }

    if (removed == 0) {
        printf("未找到歌曲: %s\n", title);
    } else {
        printf("已删除 %d 首歌曲: %s\n", removed, title);
    }
    return removed;
}

// 4. 播放歌曲
int play_song_by_title(PlaylistManager* manager, const char* title){
    Song* p = manager->head;
    while (p != NULL) {
        if (strcmp(p->title, title) == 0) {
            printf("正在播放: %s by %s\n", p->title, p->artist);
            play_audio(p->filepath);
            return 1;
        }
        p = p->next;
    }
    printf("未找到歌曲: %s\n", title);
    return 0;
}

// 5. 将播放列表保存到文件
int export_playlist(PlaylistManager* manager, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }
    Song* p = manager->head;
    while (p != NULL) {
        fprintf(fp, "%d,%s,%s,%s\n", p->id, p->title, p->artist, p->filepath);
        p = p->next;
    }
    fclose(fp);
    printf("已导出到 %s\n", filename);
    return 1;
}

// 6. 随机播放歌曲（非必做）
int play_song_random(PlaylistManager* manager) {
    if (manager->song_count == 0) {
        printf("播放列表为空\n");
        return 0;
    }
    int index = rand() % manager->song_count;
    Song* p = manager->head;
    for (int i = 0; i < index && p; i++) {
        p = p->next;
    }
    if (p) {
        printf("随机播放: %s by %s\n", p->title, p->artist);
        play_audio(p->filepath);
        return 1;
    }
    return 0;
}

// 7. 在指定位置插入歌曲（非必做）
int insert_song_at(PlaylistManager* manager, int position, const char* title, 
                   const char* artist, const char* filepath) {
    if (position < 0 || position > manager->song_count) {
        printf("插入位置无效\n");
        return 0;
    }

    Song* node = (Song*)malloc(sizeof(Song));
    if (!node) {
        printf("内存分配失败！\n");
        return 0;
    }
    node->id = (manager->tail == NULL) ? 1 : manager->tail->id + 1;
    strncpy(node->title, title, sizeof(node->title) - 1);
    node->title[sizeof(node->title) - 1] = '\0';
    strncpy(node->artist, artist, sizeof(node->artist) - 1);
    node->artist[sizeof(node->artist) - 1] = '\0';
    strncpy(node->filepath, filepath, sizeof(node->filepath) - 1);
    node->filepath[sizeof(node->filepath) - 1] = '\0';

    if (position == 0) {
        node->next = manager->head;
        manager->head = node;
        if (manager->tail == NULL) manager->tail = node;
    } else {
        Song* prev = manager->head;
        for (int i = 0; i < position - 1; i++) {
            prev = prev->next;
        }
        node->next = prev->next;
        prev->next = node;
        if (prev == manager->tail) manager->tail = node;
    }

    manager->song_count++;
    printf("已在位置 %d 插入: %s\n", position, node->title);
    return 1;
}

// 8. 销毁整个链表（非必做）
void destroy_playlist(PlaylistManager* manager) {
    Song* current = manager->head;
    while (current != NULL) {
        Song* next = current->next;
        free(current);
        current = next;
    }
    init_playlist_manager(manager);
    printf("播放列表已清空\n");
}

void display_menu() {
    printf("\n");
    printf("链表音乐播放器管理器\n");
    printf("==========================================\n");
    printf("1. 人工添加歌曲\n");
    printf("2. 显示播放列表\n");
    printf("3. 删除歌曲 (按标题)\n");
    printf("4. 播放歌曲 (按标题)\n");
    printf("5. 导出歌单\n");
    printf("6. 随机播放歌曲(非必做)\n");
    printf("7. 在指定位置添加歌曲(非必做)\n");
    printf("8. 清空播放列表(非必做)\n");
    printf("0. 退出程序\n");
    printf("==========================================\n");
    printf("请选择操作 (0-8): ");
}



// 清除输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 获取用户输入的字符串
void get_user_input(char* buffer, int size, const char* prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    // 去除换行符
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

// 主函数 - 交互式程序
int main() {
    PlaylistManager manager;
    init_playlist_manager(&manager);
    srand((unsigned int)time(NULL));
    load_songs_from_file(&manager,"song_list.txt");

    printf("=== 链表音乐播放器管理器 ===\n");
    printf("已加载 %d 首示例歌曲\n", manager.song_count);

    int choice;
    char input[100];

    do {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            printf("无效输入，请输入数字\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {               // 添加歌曲
                char title[100], artist[50], filepath[300];
                float duration;

                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                clear_input_buffer();

                add_song(&manager, title, artist, filepath);
                break;
            }
            case 2:{                // 显示播放列表 (正向)
                display_playlist(&manager);
                break;
            }
            case 3: {               // 删除歌曲 (按标题)
                char title[100];
                get_user_input(title, sizeof(title), "请输入要删除的歌曲标题: ");
                delete_songs_by_title(&manager, title);
                break;
            }
            case 4: {                 // 按歌曲名播放歌曲
                char title[100];
                get_user_input(title, sizeof(title), "请输入要播放的歌曲标题: ");
                int res = play_song_by_title(&manager, title);
                break;
            }
            case 5: {
                char path2export[300];
                get_user_input(path2export, sizeof(path2export), "请输入要导出的目标文件名: ");
                export_playlist(&manager, path2export);
                break;
            }
            case 6: {
                play_song_random(&manager);
                break;
            }
            case 7: {
                char title[100], artist[50], filepath[300];
                int position;
                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                printf("请输入歌曲插入位置: ");
                scanf("%d", &position);
                insert_song_at(&manager, position, title, artist, filepath);
                break;
            }
            case 8: {
                destroy_playlist(&manager);
                break;
            }
            case 0: // 退出程序
                printf("感谢使用链表音乐播放器管理器!\n");
                break;

            default:
                printf("无效选择，请重新输入\n");
                break;
        }

        // 暂停，让用户看到结果
        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
        }

    } while (choice != 0);

    // 清理内存
    destroy_playlist(&manager);

    return 0;
}

