from flask import Flask, render_template


app = Flask(__name__)


@app.route('/', methods=['GET', 'POST'])
def index():
	return render_template("index.html")


@app.route('/download', methods=['GET', 'POST'])
def downlaod():
	return render_template("downloadgitproejct.html")


if __name__ == '__main__':
	app.run(debug=True)
