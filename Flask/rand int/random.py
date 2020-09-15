from flask import Flask, render_template
import random

app = Flask(__name__)

@app.route('/')
def index():
    number = random.randint(1,10000)
    # the number on the left is the varibale we give template, the number on the right is what we want it to = to
    return render_template("index.html", number= number)

@app.route('/goodbye')
def bye():
    return 'Goodbye!'