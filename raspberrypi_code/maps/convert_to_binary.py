import cv2

# Read the image file
img = cv2.imread('asb9000lv.png')

# Convert the image to grayscale
gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Apply adaptive thresholding to obtain a binary image
bw_img = cv2.adaptiveThreshold(gray_img, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 15, 100)

# Display and save the binary image
cv2.imshow("Binary", bw_img)
cv2.imwrite("asb9000lv_binary.png", bw_img)
cv2.waitKey(0)
cv2.destroyAllWindows()
