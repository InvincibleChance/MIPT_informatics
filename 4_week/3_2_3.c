#include <stdio.h>
#include <string.h>

#define MAX_GAMES 100
#define MAX_TITLE_LEN 50


struct Game {
    char title[MAX_TITLE_LEN];
    int num_ratings;
    int ratings[100];
    float avg_rating;
};


float calculate_average(int *ratings, int num_ratings) {
    int sum = 0;
    for (int i = 0; i < num_ratings; i++) {
        sum += ratings[i];
    }
    return (float) sum / num_ratings;
}


void sort_games(struct Game games[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (games[j].avg_rating < games[j + 1].avg_rating) {
                Game temp = games[j];
                games[j] = games[j + 1];
                games[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Game games[MAX_GAMES];
    char temp;

    for (int i = 0; i < n; i++) {
        scanf("%c", &temp);
        scanf("%[^:]", games[i].title);
        scanf("%c", &temp);
        scanf("%d", &games[i].num_ratings);
        for (int j = 0; j < games[i].num_ratings; j++) {
            scanf("%d", &games[i].ratings[j]);
        }
        games[i].avg_rating = calculate_average(games[i].ratings, games[i].num_ratings);
    }
    sort_games(games, n);
    for (int i = 0; i < n; i++) {
        printf("%s, %.3f\n", games[i].title, games[i].avg_rating);
    }
}