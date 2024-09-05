# TODO: Add a `-x` option (or similar) for excluding weekends from the output

# Standard Library
import argparse
import calendar
import datetime
import os
import sys

def _generate_calendar(
    year:int,
    month:int,
    force:bool=False,
    weekday:bool=False
) -> int:
    # Generate file name
    file_name = f"{year}-{month:02d}.txt"

    # Don't overwrite if already exists
    if os.path.exists(file_name) and not force:
        print(f"{file_name} already exists.")
        return 1 # failure

    # Determine the format string
    if not weekday:
        format_string = "[%Y-%m-%d]"
    else:
        format_string = "[%Y-%m-%d-%a]"

    # Generate the file
    cal = calendar.Calendar()
    with open(file_name, 'w') as file:
        for date in cal.itermonthdates(year, month):
            if date.month == month:
                print(date.strftime(format_string), end="\n\n", file=file)


    return 0 # success

def _get_target_month(
    current_date:datetime.datetime,
    offset:int=0
) -> tuple[int, int]:
    year = current_date.year
    month = current_date.month + offset
    if month > 12:
        month -= 12
        year += 1
    elif month < 1:
        month += 12
        year -= 1
    return year, month

def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="Generate a monthly calendar file.")
    parser.add_argument("-c", "--current", action="store_true", help="generate calendar for current month")
    parser.add_argument("-f", "--force", action="store_true", help="force overwrite of calendar if already exists")
    parser.add_argument("-m", "--month", type=str, help="choose a month in YYYY-MM format")
    parser.add_argument("-n", "--next", action="store_true", help="generate calendar for next month")
    parser.add_argument("-p", "--previous", action="store_true", help="generate calendar for previous month")
    parser.add_argument("-w", "--weekday", action="store_true", help="include the weekday in the calendar")
    args = parser.parse_args()

    # Display help if no args given
    if len(sys.argv) == 1:
        parser.print_help()
        sys.exit(1)

    # Choose the month to use as the current month
    if args.month:
        try:
            current_date = datetime.datetime.strptime(f"{args.month}-01", "%Y-%m-%d")
        except ValueError:
            print("Error: -m argument must be given in YYYY-MM format")
            sys.exit(1)
    else:
        current_date = datetime.datetime.today()

    # Check for `force` & `weekday` flags
    force = args.force
    weekday = args.weekday

    # Return value
    rtn = 0

    # Generate calendar for current month
    if args.current or args.month:
        year, month = _get_target_month(current_date)
        rtn += _generate_calendar(year, month, force, weekday)

    # Generate calendar for next month
    if args.next:
        year, month = _get_target_month(current_date, offset=1)
        rtn += _generate_calendar(year, month, force, weekday)

    # Generate calendar for previous month
    if args.previous:
        year, month = _get_target_month(current_date, offset=-1)
        rtn += _generate_calendar(year, month, force, weekday)

    return rtn

if __name__ == "__main__":
    sys.exit(main())
