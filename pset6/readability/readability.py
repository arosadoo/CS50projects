from cs50 import get_string

text = get_string("Text: ")

words, sentences, letters = 0, 0, 0

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    if text[i] in ['!', '.', '?']:
        sentences += 1
    if not text[i] == " " and text[i-1] == " " and i > 0:
        words+=1
    if text[i].isalpha() and i == 0:
        words+=1

grade = round(0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8)


if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print("Grade", grade)
