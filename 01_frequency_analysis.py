import re
import string
import requests
from bs4 import BeautifulSoup
import matplotlib.pyplot as plt
from collections import defaultdict

def parse_random_wiki_page():
    url = "https://en.wikipedia.org/wiki/Special:Random"
    res = requests.get(url)
    html_page = res.content
    soup = BeautifulSoup(html_page, 'html.parser')
    text = soup.find_all(text=True)
    output = ''
    for t in text:
	    output += '{} '.format(t)
    output.lower()
    output = re.sub('[^a-z]+', '', output)
    return output

def get_million_letters():
    all_letters = []
    mil = int(1e6)
    while(len(all_letters) < mil):
        letters = parse_random_wiki_page()
        all_letters += letters
        print("Last parsed site contains %d letters. Total letters parsed = %d"%(len(letters),len(all_letters)))
    return all_letters[:mil]

def get_frequencies(letters):
    freq = defaultdict(int)
    for letter in letters:
        freq[letter] += 1
    freq = {k: v for k, v in sorted(freq.items(), key=lambda item: item[1], reverse=True)}
    return freq

def plot_frequencies(D):
    plt.bar(range(len(D)), list(D.values()), align='center')
    plt.xticks(range(len(D)), list(D.keys()))
    plt.show()

if __name__ == "__main__":
    letters = get_million_letters()
    freq = get_frequencies(letters)
    print(freq)
    plot_frequencies(freq)
