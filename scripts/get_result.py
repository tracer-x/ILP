import os
import csv

unbounded = "This problem is unbounded"
infeasible = "This problem is infeasible"

def collect(folder):
	lines = []
	for file in os.listdir(folder):
		line = []
		line.append(file) # Benchmark
		file_path = os.path.join(folder, file)
		with open(file_path, 'r') as f:
			data = f.read()
			if unbounded in data:
				line.append("unbounded")
			elif infeasible in data:
				line.append("infeasible")
			else:
				line.append("OK")
		lines.append(line)
	return lines

def load(file):
    bms = []
    with open(file, "rb") as f:
        for line in f:
            if line.strip():
                bms.append(line.strip())
    return bms

def order(lines, bms):
	# create data map
	dataMap={}
	for line in lines:
		dataMap[line[0]] = line[1:]
	# print(dataMap)
	# extract in order of bm
	sorted = []
	for item in bms:
		key = item + ".txt"
		if key in dataMap:
			t = [item]
			t.extend(dataMap[key])
			sorted.append(t)
		else:
			sorted.append([item, "No Result"])
	return sorted

def write_csv(outfile, lines):
    with open(outfile, 'wb') as csvfile:
        expwriter = csv.writer(csvfile, delimiter=',')
        expwriter.writerow(["Benchmark", "Result"])
        for line in lines:
            expwriter.writerow(line)

bms = load("../test/bms.txt")
# print(bms)
# print("==========")
lines = collect("../test/output")
# print(lines)
# print("==========")
sorted = order(lines, bms);
# print(sorted)
# print("==========")
write_csv("../test/result.csv", sorted)