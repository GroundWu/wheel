from flask import Flask, request, render_template
from database_operation import *
app = Flask(__name__)


@app.route('/',methods=['GET','POST'])
def home():
    return render_template('form.html')

@app.route('/submit',methods=['POST'])
def submit():
    # 获取post来的数据
    name = request.form['name']
    mail = request.form['mail']
    message = request.form['message']


    if (name and mail and message):
        insert_message(conn,name,mail,message)
        return "submit successfully!"
    return "the input can not be empty!"

@app.route('/view',methods=['GET'])
def view_message():
    messages = select(conn)
    if len(messages) == 0 or messages==None:
        return render_template('empty.html')
    return render_template('view.html',mess=messages)

if __name__ == '__main__':
    # 获取数据库连接
    conn = init_db()
    app.run()
    conn.close()