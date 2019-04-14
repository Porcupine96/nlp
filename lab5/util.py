import os


def read_bills(data_path):
    bills = {}
    for file_name in os.listdir(data_path):
        path = os.path.join(data_path, file_name)
        with open(path, 'r') as f:
            lines = f.readlines()
            bills[file_name] = '\n'.join(lines)
    return bills
