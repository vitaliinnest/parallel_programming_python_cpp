import time
import os
from multiprocessing import Pool


def sum_square(number):
	s = 0
	for i in range(number):
		s += i * i
	return s


def sum_square_with_mp(numbers, processes):
	min_time = 9999
	sum_time = 0
	
	tests = 5

	for _ in range(tests):
		start_time = time.time()
	
		p = Pool(processes)
		p.map(sum_square, numbers)

		p.close()
		p.join()

		end_time = time.time()
		execution_time = end_time - start_time
		
		sum_time += execution_time
		if min_time > execution_time:
			min_time = execution_time
	
	print(f"\nMultiprocessing (number of processes: {processes})")
	print(f"Minimal time: {min_time}s")
	print(f"Average time: {sum_time/tests}s")


def sum_square_no_mp(numbers):
	min_time = 9999
	sum_time = 0
	
	tests = 5

	for _ in range(tests):
		start_time = time.time()
	
		result = []
		for i in numbers:
			result.append(sum_square(i))

		end_time = time.time()
		execution_time = end_time - start_time

		sum_time += execution_time
		if min_time > execution_time:
			min_time = execution_time
	
	print(f"\nSerial: {execution_time}s")
	print(f"Minimal time: {min_time}s")
	print(f"Average time: {sum_time/tests}s")
	

if __name__ == '__main__':
	processes = os.cpu_count()

	numbers = range(10_000)

	for p in range(processes):
		sum_square_with_mp(numbers, p+1)
	
	sum_square_no_mp(numbers)
