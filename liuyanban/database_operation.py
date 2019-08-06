import datetime,sqlite3

def init_db():
    # 链接sqlite3数据库
    # 如果文件不存在自动创建
    # 创建一个Cursor
    # 创建message表
    # 提交

    conn = sqlite3.connect('message_db.db',check_same_thread=False)
    cursor = conn.cursor()
    sql ='create table if not exists message (id integer primary key,' \
         'user_name varchar(64),' \
         'mail_addr varchar(64),' \
         'message text,' \
         'submit_time datetime)'
    cursor.execute(sql)
    conn.commit()
    cursor.close()
    return conn

def insert_message(conn,user_name,mail,message):
    # 生成当前时间
    now = datetime.datetime.now()
    now = now.strftime('%Y-%m-%d %H:%M:%S')
    sql = 'insert into message (user_name,mail_addr,message,submit_time) values (?, ? ,? ,?)'
    cursor = conn.cursor()
    cursor.execute(sql,[user_name,mail,message,now])
    conn.commit()
    cursor.close()

def select(conn):
    sql='select * from message'
    cursor = conn.cursor()
    cursor.execute(sql)
    data = cursor.fetchall()
    cursor.close()
    return data

def close_db(conn):
    conn.close()
