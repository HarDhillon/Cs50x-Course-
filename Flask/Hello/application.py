from flask import Flask, render_template, request
import random

app = Flask(__name__)

@app.route('/')
def index():
    return render_template("index.html")

@app.route('/hello')
def hello():
    #accessing what was typed in, from the area named "name"
    name = request.args.get("name")
    if not name:
        return render_template("failure.html")
    #user will be taken to the /hello route
    return render_template("hello.html", name=name)