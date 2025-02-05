#include <bits/stdc++.h>
using namespace std;

void start() {
  cout << "Chào Mừng Bạn Đến Với Trò Chơi Nối Từ\nCách Chơi Rất Đơn Giản Bản "
          "Chỉ Cần Nhập Từ Sao Để Nối Vào Từ Đứng Trước Thành Nghĩa Có Trong "
          "Từ Điển\nBắt Đầu Trò chơi:\n";
}

string getRandomStarterWord() {
  // set thời gian chạy random
  srand(time(NULL));
  int line = rand() % 110; // random từ 1 - 110
  if (line == 0)
    line++; // nếu = 0 thì +1
            // duyệt + đọc file các từ bắt đầu game
  ifstream file("wordStart.txt");
  string word;
  int rline = 0;
  // duyệt từng dòng trong file
  while (getline(file, word)) {
    // nếu đến số dòng đã random trước đó thì dừng lại rồi trả về từ ở dòng đó
    if (rline == line) {
      file.close();
      return word;
    }
    rline++;
  }
  return "";
}

unordered_set<string> loadDictionary(const string &filename) {
  // duyệt + đọc file
  ifstream file(filename);
  // tạo set rỗng để lưu từ điển từ file
  unordered_set<string> dictionary;
  string word;
  // duyệt từng dòng và gắn vào set
  while (getline(file, word)) {
    dictionary.insert(word);
  }
  file.close();      // đóng file
  return dictionary; // trả về set từ điển
}

int checkCorrect(const string &word, const string &word2,
                 const unordered_set<string> &dictionary) {
  // gộp lại word và word2 thành 1 chuỗi để kiểm tra
  string fullWord = word + " " + word2;
  // check nếu thấy fullWord trong dictionay thì return 1
  return dictionary.find(fullWord) != dictionary.end();
}

bool repeatWord = false;
void endGame(const string &choice, int diem) {
  if (repeatWord) {
    cout << "Lặp Từ Rồi, Bạn Thua!\nSố Điểm Của Bạn Là: " << diem << endl;
    return;
  }
  // check nếu ghi exit và end game
  if (choice == "exit") {
    cout << "Bạn Đã Thoát Trò Chơi!\nSố Điểm Của Bạn Là: " << diem << endl;
    return;
  }
  cout << endl
       << "Từ Không Trong Từ Điển, Bạn Thua!\nSố Điểm Của Bạn Là: " << diem
       << endl;
  return;
}

void starGame(const unordered_set<string> &dictionary) {
  // Lấy random chữ để bắt đầu
  string word = getRandomStarterWord();
  cout << word << " ";

  // Lưu lịch sử các cặp từ đã sử dụng
  unordered_set<string> usedPairs;

  // Tạo biến để lưu điểm của người chơi
  int diem = 0;
  while (true) {
    string firstWord = word;
    string nextWord;
    cin >> nextWord;

    // Tạo cặp từ hiện tại và cặp từ ngược lại
    string currentPair = firstWord + " " + nextWord;
    string reversePair = nextWord + " " + firstWord;

    // Kiểm tra xem cặp từ ngược lại đã được sử dụng chưa
    if (usedPairs.find(reversePair) != usedPairs.end()) {
      repeatWord = true;
      endGame(nextWord, diem);
      break;
    }

    // kiểm tra xem cặp từ có giống nhau không
    if (firstWord == nextWord) {
      repeatWord = true;
      endGame(nextWord, diem);
    }

    // Kiểm tra xem cặp từ có trong từ điển không
    if (checkCorrect(firstWord, nextWord, dictionary)) {
      cout << nextWord << " ";
      word = nextWord;
      usedPairs.insert(currentPair); // Lưu cặp từ đã sử dụng
    } else {
      endGame(nextWord, diem);
      break;
    }
    diem++;
  }
}

int main() {
  start();
  // load từ điển vào set
  unordered_set<string> dictionary = loadDictionary("words.txt");
  starGame(dictionary);
  return 0;
}