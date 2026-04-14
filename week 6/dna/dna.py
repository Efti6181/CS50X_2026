import csv
import sys
def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    database_file = sys.argv[1]
    sequence_file = sys.argv[2]
    with open(database_file, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        people = [row for row in reader]
        STRs = reader.fieldnames[1:]  
    with open(sequence_file) as f:
        dna_sequence = f.read().strip()
    dna_counts = {STR: longest_match(dna_sequence, STR) for STR in STRs}
    for person in people:
        if all(int(person[STR]) == dna_counts[STR] for STR in STRs):
            print(person['name'])
            return
    print("No match")
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    sub_len = len(subsequence)
    seq_len = len(sequence)
    for i in range(seq_len):
        count = 0
        while sequence[i + count * sub_len: i + (count + 1) * sub_len] == subsequence:
            count += 1
        longest_run = max(longest_run, count)
    return longest_run
if __name__ == "__main__":
    main()
