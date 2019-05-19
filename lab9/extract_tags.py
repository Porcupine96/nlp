import xml.etree.ElementTree as ET

from main import read_bills


def extract_tags(content):
    root = ET.fromstring(content)
    print(root.tag)


tagged_bills = read_bills('./results')

extract_tags(tagged_bills.items()[0][1])
