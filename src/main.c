// strings are terrble or are they ?
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void intro() {

  // [IN REALITY C DON"T HAVE A STRING SUPPORT]
  char *s = "Hello World"; // a pointer to the first char not really a string
  printf("%s\n", s);
  // what happens if i print the size of s [i would say its 11 right?]
  printf("sizeof(s) = %zu\n", sizeof(s)); // "sizeof(s) = 8"
  // its 8 bytes/64bit address in memeory [can be diff depnding on your machine]

  // it means we can read this as int dreffernce pointer
  printf("%d\n", *s);    // 72 which is the ascicode for H
  printf("%s\n", s + 1); // "ello World" offset by 1
  /* remmaber s is just an address/pointer so we can use pointer arithmetic to
   * move the start of the string
   * what if i want to move from the right not the left ?
   * we can replace the last char with 0 but that would basiclly destory it [not
   good most of the time ]
  */

  /*
   * int n = strlen(s);
   * s[n - 1] = 0; Segmentation error string literal are read only you can't
   * touch them
   */

  /*
   * you can copy the string then replace the char you want
   * */
  char *sc = strdup(s);
  int n = strlen(sc);
  sc[n - 1] = 0;
  printf("%s\n", sc);
  // still not great u need to allocate memory just to chop from the right
  // Lets create our own string view to make it easier to do str operations
  // GO TO stringView
}

typedef struct {
  const char *data;
  size_t count;
} String_View;

void chop_from_left(String_View *s, size_t n) {
  if (n > s->count) {
    n = s->count;
  }

  s->data += n;
  s->count -= n;
}
void chop_from_right(String_View *s, size_t n) {
  if (n > s->count) {
    n = s->count;
  }

  s->count -= n;
}
void sv_trim_right(String_View *s) {
  while (s->count > 0 && isspace(s->data[s->count - 1])) {
    chop_from_right(s, 1);
  }
}
void sv_trim_left(String_View *s) {
  while (s->count > 0 && isspace(s->data[0])) {
    chop_from_left(s, 1);
  }
}
void trim(String_View *s) {
  sv_trim_left(s);
  sv_trim_right(s);
}

String_View sv(const char *s) {
  return (String_View){.data = s, .count = strlen(s)};
}

String_View trim_by_delim(String_View *s, char delim) {
  // find the delim
  size_t indx = 0;
  while (s->count > indx && s->data[indx] != delim) {
    indx++;
  }

  if (indx < s->count) {
    String_View result = {.data = s->data, .count = indx};
    chop_from_left(s, indx + 1);
    return result;
  }
  // did not find the delim
  String_View result = *s;
  chop_from_left(s, s->count);
  return result;
}

#define SV_FMT "%.*s" // for printf to read the count of chars in sv

void createStringView() {
  // using String_View we can easily do str op

  // we can convert c strings to String_View
  String_View s = sv("Hello World");
  printf("%s\n", s.data);
  // chop_from_right/chop_from_left
  chop_from_left(&s, 1);
  printf("%s\n", s.data); // ello World
  chop_from_right(&s, 1);
  printf("%s\n", s.data); // Hello World ?? why ?
  // printf dose not respect our count it keeps going until the \0

  // we have to tell it the size which is easy since we have count
  printf("%.*s\n", (int)s.count, s.data); // ello Worl

  // lets say i want to trim white spaces from a str [very common util]
  String_View s_trim = sv("   Hello World   ");
  printf("#%.*s#\n", (int)s_trim.count, s_trim.data);
  sv_trim_left(&s_trim);
  sv_trim_right(&s_trim);
  printf("#%.*s#\n", (int)s_trim.count, s_trim.data);

  // lets combine them into single op "trim"
  String_View s_trim_one = sv("   Hello World   ");
  printf("#" SV_FMT "#\n", (int)s_trim_one.count, s_trim_one.data);
  trim(&s_trim_one);
  printf("#" SV_FMT "#\n", (int)s_trim_one.count, s_trim_one.data);

  // Lets trim/chop by delim
  String_View s_trim_delm = sv("Hello, World");
  printf("Before:\n");
  printf("#" SV_FMT "#\n", (int)s_trim_delm.count, s_trim_delm.data);

  String_View s_trimed = trim_by_delim(&s_trim_delm, ',');
  printf("After:\n");
  printf("#" SV_FMT "#\n", (int)s_trim_delm.count, s_trim_delm.data);
  printf("#" SV_FMT "#\n", (int)s_trimed.count, s_trimed.data);
}

int main() { return 0; }
