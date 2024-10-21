import csv
from datetime import datetime
import time

def iso_to_unix(iso_string):
    # Parse the ISO 8601 string to a datetime object
    dt = datetime.strptime(iso_string, "%Y-%m-%dT%H:%M:%SZ")
    # Convert the datetime object to a Unix timestamp
    unix_time = int(time.mktime(dt.timetuple()))
    return unix_time

def convert_csv_dates(input_filename, output_filename):
    with open(input_filename, 'r') as infile, open(output_filename, 'w', newline='') as outfile:
        csvreader = csv.reader(infile)
        csvwriter = csv.writer(outfile)
        
        # Read the header
        header = next(csvreader)
        csvwriter.writerow(header)
        
        # Process each row
        for row in csvreader:
            # Convert the first column from ISO format to Unix time
            row[0] = iso_to_unix(row[0])
            csvwriter.writerow(row)

# Example usage
input_filename = 'Backersvej.csv'
output_filename = 'data_converted.csv'
convert_csv_dates(input_filename, output_filename)
print(f"Converted data saved to {output_filename}")