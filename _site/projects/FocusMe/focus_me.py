import cv2
import mediapipe as mp

class FaceHandZoomTracker:
    def __init__(self, min_detection_confidence=0.7, move_smooth_factor=0.05, zoom_smooth_factor=0.05, desired_area_ratio=1/8):
        self.mp_face_detection = mp.solutions.face_detection
        self.mp_hands = mp.solutions.hands
        self.face_detection = self.mp_face_detection.FaceDetection(min_detection_confidence=min_detection_confidence)
        self.hands = self.mp_hands.Hands(static_image_mode=False, max_num_hands=2, min_detection_confidence=min_detection_confidence)
        self.smooth_center_x = None
        self.smooth_center_y = None
        self.zoom_factor = 1.0
        self.move_smooth_factor = move_smooth_factor
        self.zoom_smooth_factor = zoom_smooth_factor
        self.desired_area_ratio = desired_area_ratio
        self.bbox = None
        self.zoom_box = None

    def zoom_on_box(self, frame, bbox):
        h, w, _ = frame.shape
        x, y, w_box, h_box = bbox
        center_x, center_y = x + w_box // 2, y + h_box // 2

        if self.smooth_center_x is None or self.smooth_center_y is None:
            self.smooth_center_x, self.smooth_center_y = center_x, center_y
        else:
            self.smooth_center_x = int(self.smooth_center_x + self.move_smooth_factor * (center_x - self.smooth_center_x))
            self.smooth_center_y = int(self.smooth_center_y + self.move_smooth_factor * (center_y - self.smooth_center_y))

        self.zoom_factor = max(1, self.zoom_factor)
            
        new_w, new_h = int(w // self.zoom_factor), int(h // self.zoom_factor)
        new_x = max(0, min(self.smooth_center_x - new_w // 2, w - new_w))
        new_y = max(0, min(self.smooth_center_y - new_h // 2, h - new_h))

        cropped_frame = frame[new_y:new_y + new_h, new_x:new_x + new_w]
        zoomed_frame = cv2.resize(cropped_frame, (w, h))

        self.zoom_box = (new_x, new_y, new_w, new_h)
        return zoomed_frame

    def process_frame(self, frame):
        h, w, _ = frame.shape
        frame_small = cv2.resize(frame, (w // 2, h // 2))
        frame_rgb = cv2.cvtColor(frame_small, cv2.COLOR_BGR2RGB)
        results_face = self.face_detection.process(frame_rgb)
        results_hand = self.hands.process(frame_rgb)

        boxes = []

        # 얼굴 바운딩 박스 추가
        if results_face.detections:
            for detection in results_face.detections:
                bboxC = detection.location_data.relative_bounding_box
                face_box = int(bboxC.xmin * w), int(bboxC.ymin * h), int(bboxC.width * w), int(bboxC.height * h)
                boxes.append((face_box, 'Face'))

        # 손 바운딩 박스 추가
        if results_hand.multi_hand_landmarks:
            for hand_landmarks in results_hand.multi_hand_landmarks:
                x_coords = [int(landmark.x * w) for landmark in hand_landmarks.landmark]
                y_coords = [int(landmark.y * h) for landmark in hand_landmarks.landmark]
                hand_box = (min(x_coords), min(y_coords), max(x_coords) - min(x_coords), max(y_coords) - min(y_coords))
                boxes.append((hand_box, 'Hand'))

        # 얼굴과 손을 포함하는 최소 사각형 계산
        if boxes:
            x_min = min([box[0][0] for box in boxes])
            y_min = min([box[0][1] for box in boxes])
            x_max = max([box[0][0] + box[0][2] for box in boxes])
            y_max = max([box[0][1] + box[0][3] for box in boxes])

            self.bbox = (x_min, y_min, x_max - x_min, y_max - y_min) ############

            # 줌 인/아웃 팩터 계산
            box_area = self.bbox[2] * self.bbox[3]
            desired_area = (h * w) * self.desired_area_ratio
            self.target_zoom_factor = (desired_area / box_area) ** 0.5
            self.zoom_factor += self.zoom_smooth_factor * (self.target_zoom_factor - self.zoom_factor)

            frame = self.zoom_on_box(frame, self.bbox)

        elif self.smooth_center_x is not None and self.smooth_center_y is not None:
            # 얼굴이 감지되지 않아도 이전의 줌 상태 유지
            frame = self.zoom_on_box(frame, self.bbox)

        return frame

# 그림 그리기
def draw_box_and_data(frame, bbox, label='Box'):
    x, y, w, h = bbox
    # 박스 그리기
    cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 255, 255), 2)
    # 중심점 그리기
    center_x, center_y = x + w // 2, y + h // 2
    cv2.circle(frame, (center_x, center_y), 5, (0, 0, 255), -1)
    # 박스 데이터 표시
    cv2.putText(frame, f'{label}', (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

def main():
    cap = cv2.VideoCapture(0) 
    tracker = FaceHandZoomTracker()

    while True:
        ret, frame = cap.read()
        frame = cv2.flip(frame, 1)
        if not ret:
            break

        # 프레임 처리
        processed_frame = tracker.process_frame(frame)

        # 줌된 영역 표시
        if tracker.zoom_box is not None:
            draw_box_and_data(frame, tracker.zoom_box, label='Zoomed Area')

        # 얼굴과 손의 박스 및 중심점 표시
        if tracker.bbox is not None:
            draw_box_and_data(frame, tracker.bbox, label='Bounding Box')

        # 화면 병합 및 출력
        combined_frame = cv2.hconcat([frame, processed_frame])
        cv2.imshow('Focus_Me', combined_frame)

        if cv2.waitKey(1) & 0xFF == 27:
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
