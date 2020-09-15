from flask import Flask, redirect, render_template, request, session
from flask_session import Session

app = Flask(__name__)
app.config["SESSION_PERMANENT"] = False
#store data on the computers filesystem
app.config["SESSION_TYPE"] = "filesystem"
#using session on this app
Session(app)


@app.route("/")
def tasks():
    #if user does not have todos dictionary in their session, we create one
    if "todos" not in session:
        session["todos"] = []
    return render_template("tasks.html", todos=session["todos"])

@app.route("/add", methods=["GET", "POST"])
def add():
    if request.method =="GET":
        return render_template("add.html")
    else:
        todo = request.form.get("task")
        #adding the users submission to their own local todo list as well
        session['todos'].append(todo)
        return redirect("/")