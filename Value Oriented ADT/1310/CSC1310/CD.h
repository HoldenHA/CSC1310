#if !defined CD_H
#define CD_H

#include "Song.h"
#include "Text.h"
using CSC1310::String;
#include "ListArray.h"
using CSC1310::ListArray;

namespace CSC1310
{
class CD
{
   private:
      String* artist;
      String* title;

      int year;
      int rating;
      int num_tracks;

      ListArray<Song>* songs;

   public:
      CD(String* artist, String* title, int year, int rating, int num_tracks);
      virtual ~CD();

      String* getKey();
      String* getArtist();
      void addSong(String* title, String* length);
      void displayCD();

      static ListArray<CD>* readCDs(const char* file_name);

      static int compare_items(CD* one, CD* two);
      static int compare_keys(String* sk, CD* cd);
      static char getRadixChar(CD* cd, int index);  //1-based
};
}

#endif
