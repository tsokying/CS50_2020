from flask import Flask, g, render_template, request, redirect
import sqlite3 

app = Flask(__name__)

DATABASE = "lecture.db"

def get_db():
	db = getattr(g, '_database', None)
	if db is None:
		db = g._database = sqlite3.connect(DATABASE)
	return db

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()

def init_db():
    with app.app_context():
        db = get_db()
        with app.open_resource('schema.sql', mode='r') as f:
            db.cursor().executescript(f.read())
        db.commit()

def remove_db():
    if os.path.isfile(DATABASE):
        os.remove(DATABASE) 

@app.route("/")
def index():
	db = get_db()
	rows = db.execute("SELECT * from registrants")
	return render_template("index.html", rows=rows)

@app.route("/register", methods=["GET", "POST"])
def register():
	if request.method == "GET":
		return render_template("register.html")
	else:
		name = request.form.get("name")
		if not name:
			return render_template("apology.html", message="You must provide a name.")
		email = request.form.get("email")
		if not email:
			return render_template("apology.html", message="You must provide a name.")
		db = get_db()
		db.execute("INSERT INTO registrants (name, email) VALUES (?, ?)", (name, email))
		db.commit()
		return redirect("/")
