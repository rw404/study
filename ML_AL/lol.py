from sklearn.nayve_bayes import *

corpus = [['list of ll'], ['class']]

classifier = GaussianNB()

vectorizer = CountVectorizer(ngram_range=(1, 2))
y = corpus[1]
X = vectorizer.fit_transform(corpus[0])
classifier.fit(X, y)

new_texts = ["texts"]
feats = vectorizer.transform(new_texts)
print(classifier.predict(feats))
