#!/usr/bin/env python
# coding=utf-8
# jtoh.py

import json
import os
import shutil
import sys
import getopt


def takeSecond(elem):
    return elem[1]

def build_env():
    c_path = ["html"]
    for p in c_path:
        if os.path.exists(p):
            shutil.rmtree(p)
        os.mkdir(p)


def decode_json(json_file = "./coverity.json", message_list = {}, message_count_list = {}):
    jfile = open(json_file,"r")
    jstr = jfile.read()
    jobj = json.loads(jstr)

    for issu in jobj["issues"]:
        for event in issu["events"]:
            file_name =  event["filePathname"]
            line = event["lineNumber"]
            column = event["columnNumber"]
            desc = "<b>" + issu["type"] + "-</b>" + event["eventDescription"]
            MISRACategory = "default"
            if "MISRACategory" in issu["checkerProperties"].keys():
                MISRACategory = issu["checkerProperties"]["MISRACategory"]
            msg = (file_name, line, column, desc, MISRACategory)
            if file_name in message_list.keys():
                message_list[file_name].append(msg)
                message_count_list[file_name]["total"] = message_count_list[file_name]["total"] + 1
                if MISRACategory in message_count_list[file_name].keys():
                    message_count_list[file_name][MISRACategory] = message_count_list[file_name][MISRACategory] + 1
                else:
                    message_count_list[file_name][MISRACategory] = 1

            else:
                message_list[file_name] = [msg]
                msg_cnt = {}
                for key in ("total", "Required", "Advisory", "Automated", "Partially", "Non-automated"):
                    if key  == "total" or key == MISRACategory:
                        msg_cnt[key] = 1
                    else:
                        msg_cnt[key] = 0
                message_count_list[file_name] = msg_cnt
    jfile.close();

def create_html_details(src_file_name, dst_file_name, messages, priority):
    details_template = """
<!DOCTYPE HTML PUBLIC "">
<html>

<head>
    <title>Coverity error reader: {file_name}
    </title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
</head>

<style type="text/css">
    .Required{{
        background-color:rgb(237, 129, 129);
    }}
    .Advisory{{background-color:rgb(243, 135, 185);}}
    .Inaddition{{background-color:rgb(201, 218, 241);}}
    .Automated{{background-color:rgb(207, 240, 191);}}
    .Partially{{background-color:rgb(174, 232, 215);}}
    .Non-automated{{background-color:rgb(241, 241, 105);}}
    .default {{        background-color:silver}}
</style>

<body>
<pre style="color:rgb(22, 36, 36); font-size: large; font-family: 'Courier New', Courier, monospace;">
<code>{line_infos}</code>
</pre>
</body>

</html>
"""
    # details_line_template = """<b><a name="line{line_number}">          {line_number}    </a></b>{rline}"""
    details_line_template = """<a name="line{line_number}">          {line_number}    </a>{rline}"""
    details_error_line_template = """<a class="{style}">{rline}</a>
"""

    error_count = len(set(messages))
    if os.path.exists(src_file_name):
        line_infos = ""
        cfile = open(src_file_name, "r")
        read_line_count = 1
        msg_index = 0
        for rline in cfile.readlines():
            line_infos = line_infos + details_line_template.format(line_number = read_line_count, rline = rline)
            while msg_index < error_count and read_line_count == messages[msg_index][1]:
                if priority in ("all", messages[msg_index][4]):
                    line_infos = line_infos + details_error_line_template.format(style = messages[msg_index][4], rline = messages[msg_index][3])
                msg_index = msg_index + 1
            read_line_count = read_line_count + 1
        cfile.close()
        detail_html = details_template.format(file_name = src_file_name, line_infos = line_infos)
        ofhtml = open(dst_file_name, "w")
        ofhtml.write(detail_html)
        ofhtml.close()

def create_html(message_list, message_count_list):
    index_frame_template = """
<!DOCTYPE html PUBLIC "">
<html>

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Coverity Errors</title>
</head>

<body bgcolor="#FFFFFF" text="#000000" link="#37598D" vlink="#5685AB">
    <center>
        <h2>Coverity Errors</h2>
    </center>
    <table cellPadding="8" summary="defects">
        <tr bgColor="#4682B4">
            <td>ID</td>
            <td>Checker</td>
            <td>File</td>
            <td>Errors</td>
            <td>Required</td>
            <td>Advisory</td>
            <td>Automated</td>
            <td>Partially</td>
            <td>Non-automated</td>
        </tr>
        {index_tb_body}
    </table>
</body>

</html>
"""
    index_detail_template = """
    <tr bgcolor="#F8F8F2" class="bodytextlarge">
        <td>{index_tb_id}</td>
        <td>clang</td>
        <td><a
                href="{details_url}">{file_name}</a>
        </td>
        <td><a href="{details_url}">{error_count} </a></td>
        <td><a href="{details_url}.Required.html">{error_count_re} </a></td>
        <td><a href="{details_url}.Advisory.html">{error_count_ad} </a></td>
        <td><a href="{details_url}.Automated.html">{error_count_au} </a></td>
        <td><a href="{details_url}.Partially.html">{error_count_par} </a></td>
        <td><a href="{details_url}.Non-automated.html">{error_count_non} </a></td>
    </tr>
"""

    index_tb_id = 0
    index_tb_body = ""
    for file_name, messages in message_list.items():
        error_count = message_count_list[file_name]["total"]
        error_count_re = message_count_list[file_name]["Required"]
        error_count_ad = message_count_list[file_name]["Advisory"]
        error_count_au = message_count_list[file_name]["Automated"]
        error_count_par = message_count_list[file_name]["Partially"]
        error_count_non = message_count_list[file_name]["Non-automated"]

        details_url = str(index_tb_id) + "_" + os.path.basename(file_name) + ".html"
        index_tb_body = index_tb_body + index_detail_template.format(index_tb_id = index_tb_id,
                                                                     details_url = details_url,
                                                                     file_name = file_name,
                                                                     error_count = error_count,
                                                                     error_count_re = error_count_re,
                                                                     error_count_ad = error_count_ad,
                                                                     error_count_au = error_count_au,
                                                                     error_count_par = error_count_par,
                                                                     error_count_non = error_count_non
                                                                    )
        index_tb_id = index_tb_id + 1

        print("====> file_name:", os.path.basename(file_name), "error_count:", error_count)

        messages.sort(key=takeSecond)
        for priority in ("all", "Required", "Advisory", "Automated", "Partially", "Non-automated"):
            if priority == "all":
                create_html_details(file_name, "html/" + details_url, messages, priority);
            elif message_count_list[file_name][priority] > 0:
                create_html_details(file_name, "html/" + details_url + "." + priority + ".html", messages, priority);

    # 1. create index html
    index_html = index_frame_template.format(index_tb_body = index_tb_body)
    findex = open("html/index.html", "w")
    findex.write(index_html)
    findex.close();




if __name__ == "__main__":
    message_list = {}
    message_count_list = {}
    json_file = "./coverity.json"

    opts, args = getopt.getopt(sys.argv[1:], "hi:", ["help", "input_file="])
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            print("jtoh.py [-i <input_file>]")
            print("or jtoh.py [--input_file=<input_file>]")
            sys.exit()
        elif opt in ("-i", "--input_file"):
           json_file = arg

    build_env()
    decode_json(json_file, message_list, message_count_list)
    create_html(message_list, message_count_list)
