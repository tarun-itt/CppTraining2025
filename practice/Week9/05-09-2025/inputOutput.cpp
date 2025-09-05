#include <fstream>
#include <iostream>
#include <thread>

#include "BlockingQueue.hpp"

void input_worker(std::istream &in, BlockingQueue<std::string> &input_queue) {
  std::string line;
  while (std::getline(in, line)) {
    input_queue.push(std::move(line));
  }
  input_queue.shutdown();
}

void output_worker(std::ostream &out,
                   BlockingQueue<std::string> &output_queue) {
  while (true) {
    auto line = output_queue.pop();
    if (!line)
      break;
    out << *line << '\n';
    out.flush();
  }
}

int main(int argc, char *argv[]) {
  std::unique_ptr<std::ifstream> file_in;
  std::istream *input_stream = &std::cin;

  if (argc > 1) {
    file_in = std::make_unique<std::ifstream>(argv[1]);
    if (!file_in->is_open()) {
      std::cerr << "Error opening input file\n";
      return 1;
    }
    input_stream = file_in.get();
  }

  std::unique_ptr<std::ofstream> file_out;
  std::ostream *output_stream = &std::cout;

  if (argc > 2) {
    file_out = std::make_unique<std::ofstream>(argv[2]);
    if (!file_out->is_open()) {
      std::cerr << "Error opening output file\n";
      return 1;
    }
    output_stream = file_out.get();
  }

  BlockingQueue<std::string> input_queue;
  BlockingQueue<std::string> output_queue;

  std::thread input_thread(input_worker, std::ref(*input_stream),
                           std::ref(input_queue));

  std::thread output_thread(output_worker, std::ref(*output_stream),
                            std::ref(output_queue));

  while (true) {
    auto input = input_queue.pop();
    if (!input)
      break;

    std::string processed;
    processed.reserve(input->size());
    for (char c : *input) {
      processed +=
          static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }

    output_queue.push(std::move(processed));
  }

  output_queue.shutdown();

  input_thread.join();
  output_thread.join();

  return 0;
}
