all: Exam

run: Exam
	./Exam

test: Exam
	python3 ./test.py

Exam: exam.cpp
	g++ -o Exam exam.cpp -pthread
